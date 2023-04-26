import boto3
import json


def main():
	topicArn = 'arn:aws:sns:us-east-1:479452557090:triggerLambda'
	print("In requestLocation.py")
	snsClient = boto3.client(
	'sns',
	aws_access_key_id = "AKIAW7IMZN4ROAYI3RPC",
	aws_secret_access_key = "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",
	region_name = 'us-east-1'
	)
	publishObject = {"message":"bitch boy"}
	
	response = snsClient.publish(TopicArn=topicArn,
	Message=json.dumps(publishObject),
	Subject = "HOE",
	MessageAttributes = {"Message":{'DataType':"String","StringValue":"SLUT"}})
	
	print(response['ResponseMetadata']['HTTPStatusCode'])
	
	

