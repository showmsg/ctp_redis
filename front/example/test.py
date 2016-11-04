from client import APITest
api = APITest("http://127.0.0.1:5000")

data = api.login('showmsg', '1')
print data.get('message')

data = api.user()
print data
print data.get('nickname')
data = api.logout()
print data

print data.get('message')