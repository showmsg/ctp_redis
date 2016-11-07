# coding:utf-8
from flask import Flask, request, jsonify, g, Response, make_response, abort,render_template,session
from model import * 
from environment import db_session,init_db
import hashlib
import time
import redis
from functools import wraps
from config import *
from flask_socketio import SocketIO, Namespace, emit, join_room, leave_room, \
        close_room, rooms, disconnect

init_db()
async_mode = None
app = Flask(__name__)
app.config.from_object('config')
app.config['SECRET_KEY'] = 'you just a pig'
socketio = SocketIO(app, async_mode=async_mode)
thread = None

redis_store = redis.Redis(host= REDIS_HOST, port=REDIS_PORT, db=REDIS_DB, password=REDIS_PWD)

@app.errorhandler(400)
def bad_request(error):
    return make_response(jsonify({'error': 'Bad request'}), 400)


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)

def login_check(f):
    @wraps(f)
    def decorator(*args, **kwargs):
        token = request.headers.get('token')
        if not token:
            return jsonify({'code': 0, 'message': '需要验证'})

        username = redis_store.get('token:%s' % token)
        if not username or token != redis_store.hget('user:%s' % username, 'token'):
            return jsonify({'code': 2, 'message': '验证信息错误'})

        return f(*args, **kwargs)
    return decorator


@app.before_request
def before_request():
    token = request.headers.get('token')
    username = redis_store.get('token:%s' % token)
    print 'before_request:%s' % username
    if username:
        g.current_user = User.query.filter_by(username=username).first()
        g.token = token
    return


@app.route('/login', methods=['POST'])
def login():
    username = request.get_json().get('username')
    password = request.get_json().get('password')
    print 'login:%s' % username
    user = User.query.filter_by(username=username).first()
    if not user:
        return jsonify({'code': 0, 'message': '没有此用户'})

    if user.password != password:
        return jsonify({'code': 0, 'message': '密码错误'})

    m = hashlib.md5()
    m.update(username)
    m.update(password)
    m.update(str(int(time.time())))
    token = m.hexdigest()

    pipeline = redis_store.pipeline()
    pipeline.hmset('user:%s' % user.username, {'token': token, 'nickname': user.nickname, 'app_online': 1})
    pipeline.set('token:%s' % token, user.username)
    pipeline.expire('token:%s' % token, 3600*24*30)
    pipeline.execute()

    return jsonify({'code': 1, 'message': '成功登录', 'nickname': user.nickname, 'token': token})

@app.route('/market')
def index():
    return render_template('index.html', async_mode=socketio.async_mode)

def background_thread():
    """Example of how to send server generated events to clients."""
    count = 0
    while True:
        socketio.sleep(10)
        count += 1
        socketio.emit('my_response',
                {'data': 'Server generated event', 'count': count},
                namespace='/test')

class MyNamespace(Namespace):
    def on_join(self, message):
        join_room(message['room'])
        session['receive_count'] = session.get('receive_count', 0) + 1

        pipline = redis_store.pubsub()
        pipline.subscribe(['01:channel:zn1702'])
        for item in pipline.listen():
            emit('my_response',
                    {'data': item['data'], 'count': session['receive_count']})
    def on_leave(self, message):
         leave_room(message['room'])
         session['receive_count'] = session.get('receive_count', 0) + 1
         emit('my_response',
              {'data': 'In rooms: ' + ', '.join(rooms()),
               'count': session['receive_count']})
    def on_connect(self):
        global thread
        if thread is None:
            thread = socketio.start_background_task(target=background_thread)
        emit('my_response', {'data': 'Connected', 'count': 0})

    def on_disconnect(self):
        print('Client disconnected', request.sid)

socketio.on_namespace(MyNamespace('/test'))

@app.route('/user')
@login_check
def user():
    user = g.current_user

    nickname = redis_store.hget('user:%s' % user.username, 'nickname')
    return jsonify({'code': 1, 'nickname': nickname, 'username': user.username})


@app.route('/logout')
@login_check
def logout():
    user = g.current_user

    pipeline = redis_store.pipeline()
    pipeline.delete('token:%s' % g.token)
    pipeline.hmset('user:%s' % user.username, {'app_online': 0})
    pipeline.execute()
    return jsonify({'code': 1, 'message': '成功注销'})


@app.teardown_request
def handle_teardown_request(exception):
    db_session.remove()
