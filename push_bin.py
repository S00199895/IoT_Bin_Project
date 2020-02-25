from datetime import datetime
from pymongo import MongoClient

def push_bin(vol, db):

    vol = 50
    time = datetime.now()

    bin = {
       'percentage_full': vol,
       'datetime': time
    } 
    res = db.insert_one(bin)
    return [bin, res.inserted_id]
