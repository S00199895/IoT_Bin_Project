from pymongo import MongoClient
from pprint import pprint

client = MongoClient("mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority")
db = client.bintestdb

def pull_first_res():
    res = db.bintestdb.find().sort('datetime').limit(1)
    return res[0]

pprint(pull_first_res())