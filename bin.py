from pymongo import MongoClient
from pprint import pprint
from datetime import datetime
#from bridgeclient import Bridgeclient as bridgeclient
import push_bin
import pull_most_recent

client = MongoClient('mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority')
db = client.bintestdb
#board = bridgeclient()

push_bin.push_bin(50, db)
pprint(pull_most_recent.pull_first_res(db))