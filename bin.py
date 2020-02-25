from pymongo import MongoClient
from pprint import pprint
from datetime import datetime
#from bridgeclient import Bridgeclient as bridgeclient
import push_bin as push
import pull_results as pull

client = MongoClient('mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority')
db = client.bintestdb
db = db.bintestdb

#board = bridgeclient()

push.push_bin(50, db)
pprint(pull.pull_first_res(db))
