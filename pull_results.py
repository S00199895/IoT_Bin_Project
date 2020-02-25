from pymongo import MongoClient
from pprint import pprint

client = MongoClient('mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority')
db = client.bintestdb

def pull_first_res(db):
    # pulls most recent result from db
    res = db.find().sort('datetime', -1).limit(1)
    return res[0]

def pull_all_res(db):
    # pulls all results from db
    res = db.find().sort('datetime', -1)
    return res