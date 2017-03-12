import nltk

class Analyzer():
    """Implements sentiment analysis."""
    
    #list for loaded words from the files
    positiveList = []  
    negativeList = []
    
    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""
        #opening the files
        self.positiveFile= open(positives, "r")
        self.negativeFile= open(negatives, "r")
        
        #loading file into the lists and deleting the \n new string symbol
        for pline in self.positiveFile:
            Analyzer.positiveList.append(pline.replace("\n",""))
        
        for nline in self.negativeFile:
            Analyzer.negativeList.append(nline.replace("\n",""))
            
        #closing files
        self.positiveFile.close()
        self.negativeFile.close()
    
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        text = tokenizer.tokenize(text)
        
        #word analyze
        for line in text:
        #count(line.lower) - returns the input word in lower case for correct comparison with the list
            if Analyzer.positiveList.count(line.lower()): 
                score += 1 
            elif Analyzer.negativeList.count(line.lower()):
                score -= 1
        return score