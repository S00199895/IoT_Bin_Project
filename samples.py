from pymongo import MongoClient
from random import randint, randrange
from datetime import datetime, timedelta

client = MongoClient("mongodb+srv://test:FioTestPass@bindata-lhxe1.mongodb.net/test?retryWrites=true&w=majority")
db = client.bintestdb

def random_date(start, end):
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    return start + timedelta(seconds=random_second)

names = ['test1', 'test2', 'test3']
d1 = datetime.strptime('1/2/2020 6:00 AM', '%d/%m/%Y %I:%M %p')
d2 = datetime.strptime('26/2/2020 6:00 PM', '%d/%m/%Y %I:%M %p')

for x in range(1, 501):
    bin = {
        'name' : names[randint(0, len(names) - 1)],
        'percent_full' : randint(0, 101),
        'datetime' : random_date(d1, d2)
    }

    result = db.bintestdb.insert_one(bin)

    print('Created {0} of 500 as {1}'.format(x, result.inserted_id))

print('Finished creating 500 bin tests')