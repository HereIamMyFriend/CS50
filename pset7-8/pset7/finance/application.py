from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir


from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    #query for user balance
    rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    
    #query for user stocks
    data = db.execute("""SELECT symbol, SUM(amount) AS amount FROM purchase WHERE user_id=:user_id
            GROUP BY symbol HAVING SUM(amount) > 0""", user_id=session["user_id"])    
            
    #storing user balance in cash
    cash = rows[0]["cash"]
    summary = 0
    
    #loop for list returned by db.execute for the table rendering
    for line in data:
        tmp = lookup(line["symbol"])
        line["name"] = tmp["name"]
        line["price"] = tmp["price"]
        line["total"] = line["price"] * line["amount"]
        summary += line["total"]

    summary += cash      
    return render_template("index.html", data=data, bank=cash, cash=summary)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    #if user clicks the "Buy" button
    if request.method == "POST":
        
        #Validate users input
        if not request.form.get("shares"):
            return apology("Enter the stock's symbol")
        
        if not request.form.get("quantity") or int(request.form.get("quantity")) < 0:
            return apology("Enter correct amount of the shares")
        #look for the entered symbol
        line = lookup(request.form.get("shares"))
        
        if not line:
            return apology("Invalid stock's symbol")
        
        #query for user balance     
        current_cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        
        #total price for the stocks
        cost = line["price"] * int(request.form.get("quantity"))
        
        #check the buying possibility 
        if current_cash[0]["cash"] < cost:
            return apology("Not enough money!")
        
        cash_update = current_cash[0]["cash"] - cost
        
        #update user balance after buying
        db.execute("UPDATE users SET cash =:cash WHERE id =:id", cash=cash_update, id=session["user_id"])
    
        #storing info about purchase into the db table
        db.execute("""INSERT INTO purchase (user_id, symbol, name, amount, price, total) 
                    VALUES (:user_id, :symbol, :name, :amount, :price, :total)""",
                    user_id=session["user_id"], symbol=line["symbol"], name=line["name"], amount=request.form.get("quantity"),
                    price=line["price"], total=cost)
                          
        #info
        flash("Already bought!")
         #return to the homepage
        return redirect (url_for("index"))
    else:
        #if method == GET
        return render_template("buy.html")
    


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    #get list with information from the db
    purchase = db.execute("SELECT * FROM purchase WHERE user_id=:user_id", user_id=session["user_id"])
    
    #render the history table
    return render_template("history.html", purchase=purchase)
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    
    """Get stock quote."""
    
    #if the user clicks the "Quote" button
    if request.method == "POST":
    
        #validate user input
        if not request.form.get("quote"):
            return apology("Enter the stock's symbol")
        #look for the entered symbol    
        line = lookup(request.form.get("quote"))
        
        if not line:
            return apology("Something went wrong (invalid symbol) :(")
        else:
            #output message for the user on the /quote page
            row = "A share of " + line["name"] + "(" + line["symbol"] + ")" + " —" + " costs " + usd(line["price"])
            
        return render_template("quoted.html", text = row)
      
    if request.method == "GET":
        return render_template("quote.html")
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    #if the user click the "Register" button
    if request.method == "POST":
        
        #validate user input
        if not request.form.get("username"):
            return apology("must provide username!")

        if not request.form.get("password"):
            return apology("must provide password!")
            
        if not request.form.get("password-repeat"):
            return apology("Repeat-password form is also required")
        
        if request.form.get("password") != request.form.get("password-repeat"):
            return apology("Passwords do not match")
        
        #cheking name for the uniqueness    
        rows = db.execute("SELECT * FROM users WHERE username = :username", username = request.form.get("username"))
        if len(rows) != 0:
            return apology("Such user is already exist!")
        
        #add the new user name and hashed password to the db
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username = request.form.get("username"), hash = pwd_context.encrypt(request.form.get("password")))
        
        #info if success
        flash("Registered!")
         #return to the homepage
        return redirect(url_for("index"))
    else:
        #if user clicked the "Register" button in main navigation bar
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    #if users clicked the "Sell" button
    if request.method == "POST":
        #validate user input
        if not request.form.get("shares"):
            return apology("Enter the stock's symbol")
        
        shares = int(request.form.get("quantity"))
        
        if not request.form.get("quantity") or shares < 0:
            return apology("Enter correct amount of the shares")
            
        #does user has a correct amount of stocks he wanted to sell
        rows = db.execute("""SELECT SUM(amount) AS amount FROM purchase WHERE user_id=:user_id
                        AND symbol=:symbol GROUP BY symbol""", user_id=session["user_id"], symbol = request.form.get("shares").upper())
        
        if len(rows) == 0:
            return apology("The share is not owned")
    
        if rows[0]["amount"] < shares:
            return apology("Invalid amount of the shares!")
        
        #store amount of stocks
        line = lookup(request.form.get("shares"))
        
        #store user current cash
        current_cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
    
        #update cash after buying
        cash_update = current_cash[0]["cash"] + (line["price"] * shares)
        
        #total price of the purchase
        total_worth = line["price"] * shares
        
        #update user cash
        db.execute("UPDATE users SET cash =:cash WHERE id =:id", cash=cash_update, id=session["user_id"])
        
        #store the data about sold stocks
        db.execute("INSERT INTO purchase (user_id, symbol, amount, price) VALUES (:user_id, :symbol, :amount, :price)",
                            user_id=session["user_id"], symbol=line["symbol"], amount=(-shares), price=line["price"])
    
        flash ("Sold!")
        #return to the homepage
        return redirect(url_for("index"))
    else:
        #if user click the "Sell" button in main-navigation menu
        return render_template("sell.html")
        
@app.route("/new_password", methods=["GET", "POST"])
@login_required
def new_password():
    """Allows user to change the password"""
    
    #if user clicked the "Change" button
    if request.method == "POST":
        
        #validate user input
        if not request.form.get("old-password"):
            return apology("missing your old password")
        if not request.form.get("new-password"):
            return apology("enter your new password")
            
        #query to get old password hash   
        password = db.execute("SELECT hash FROM users WHERE id=:user_id", user_id=session["user_id"])
        
        #validate "old-password" input with to hashed password from db
        if not pwd_context.verify(request.form.get("old-password"), password[0]["hash"]):
            return apology("Invalid user password")
        
        #hash the new password
        new_hash = pwd_context.encrypt(request.form.get("new-password"))
        
        #update password
        db.execute("UPDATE users SET hash=:new_hash WHERE id=:user_id", new_hash=new_hash, user_id=session["user_id"])
        
        flash("The password was successfully changed")
        return redirect(url_for("index"))
    else:
        #if user clicked the "Change password" button
        return render_template("new_password.html")