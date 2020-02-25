# Test for Arduino Yun to mongoDB
# Uses py 3.8
#
# Dependancies:
# pymongo
# pymongo[srv]
#
# user:test
# connection string: mongodb+srv://test:<password>@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority

from pymongo import MongoClient
from pprint import pprint

client = MongoClient("mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority")
db = client.bintestdb

serverStatusResult = db.command("serverStatus")
pprint(serverStatusResult)
