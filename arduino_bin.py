#!usr/bin/python

import sys
from pymongo import MongoClient
from pprint import pprint
from datetime import datetime
from bridgeclient import Bridgeclient as bridgeclient
import push_bin as push
import pull_results as pull

# SET IR SERNSOR TO PIN A1
# SET MOTION SENSOR TO PIN D3
IR_SENSOR = 'A1'
MOTION_SENSOR = 'D3'

client = MongoClient('mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority')
db = client.bintestdb
db = db.bintestdb

board = bridgeclient()

vol = board.get(IR_SENSOR)
push.push_bin(vol, db)
pull.pull_first_res(db)
