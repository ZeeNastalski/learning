conn = new Mongo("localhost:27017");
db = conn.getDB("testdb");
cursor = db.getCollection('myCollection').find({});

while ( cursor.hasNext() ) {
   printjson( cursor.next() );
}