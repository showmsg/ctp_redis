# coding:utf-8
from sqlalchemy import create_engine, MetaData
from sqlalchemy.orm import scoped_session, sessionmaker

engine = create_engine("mysql://root:12345678@127.0.0.1:3306/front?charset=utf8", pool_recycle=7200)

metadata = MetaData()

db_session = scoped_session(sessionmaker(autocommit=False,
                                         autoflush=False,
                                         bind=engine))
def init_db():
	metadata.create_all(bind=engine)