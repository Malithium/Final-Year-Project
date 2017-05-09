import praw
import json
from textblob import TextBlob
import re
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from nltk import tokenize
import nltk

class Object:
    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, 
            sort_keys=True, indent=4)	
    
def getSentiment(body):
	finalScore = 0
	roundedFinalScore = 0
	sid = SentimentIntensityAnalyzer()
	comLines = tokenize.sent_tokenize(body)
	for line in comLines:
		ss = sid.polarity_scores(line)
		lineCompoundScore = ss['compound']
		finalScore += lineCompoundScore	

	roundedFinalScore = round(finalScore/len(comLines),4)
	return roundedFinalScore
    
def getComments():
	with open("ResourceData.json") as data_file:
		data = json.load(data_file)
	r = praw.Reddit(user_agent = data["User_Agent"], client_id= data["Client_Id"], client_secret=data["Client_Secret"])
	sub = r.subreddit(data["Sub_Reddit"])
	subName = sub.fullname
	d = Object()
	d.subject = subName
	d.topics = []
	print("retrieving submissions")
	
	#iterate over each submission
	counter = 0
	i = 1;
	for submission in sub.top(limit=5, time_filter='day'):
		counter = counter + 1
		submission.comments.replace_more(limit=0)	
		cList = []
		rList = []	
		comment_queue = submission.comments[:]
		top = Object()
		top.topic = submission.title
		top.id = submission.fullname

		while comment_queue:
			comment = comment_queue.pop(0)
			if comment.author != None:
				con = Object()
				con.id = comment.id
				con.body = re.sub(' +',' ',comment.body.replace('\n', ' ').replace('\r',' '))
				con.polarity = getSentiment(con.body)
				con.parent_id = comment.parent_id
				author = comment.author
				if author != None:
					con.author = author.name
				else:
					con.author = "none"
				#con.user = author.fullname
				if i == 1:
					print(author.name)
					i = 0
				if comment.parent_id == submission.fullname:
					con.reply = False
				else:
					con.reply = True
				cList.append(con)
				comment_queue.extend(comment.replies)
	
		#iterate over each comment in the comment list
		top.comments = cList
		d.topics.append(top)
		print("\rGenerated Objects : " + str(counter))
		
	print("Generating JSON file")
	with open('data.json', 'w') as outfile:
		outfile.write(d.toJSON())
		outfile.close()

getComments()
