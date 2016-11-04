#coding:utf-8

from sqlalchemy import Table, Column, Integer, String, ForeignKey,DateTime
from sqlalchemy.orm import mapper 
from environment import metadata, db_session
import datetime

class User(object):
    query = db_session.query_property()
    def __init__(self, username=None, password=None):
        self.username = username
        self.password = password
    def __repr__(self):
        return 'User %s' % (self.username)

users = Table('user', metadata,
        Column('id', Integer, primary_key=True),
        Column('username', String(20), index=True, nullable=False),
        Column('password', String(30), nullable=False),
        Column('nickname', String(30), index=True, nullable=False),
        Column('role', Integer, default=0),
        Column('functions', String(256)),
        Column('isactive', Integer, default=0),
        Column('login_times', Integer, default=0),
        Column('phone_number', String(11), index=True, nullable=False),
        Column('register_time', DateTime, index=True, default=datetime.datetime.now),
        Column('last_time', DateTime, default=datetime.datetime.now)
        )
mapper(User, users)
