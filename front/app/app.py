from model import *
from view import *

if __name__ == '__main__':
	socketio.run(app, debug=True,  host='0.0.0.0', port=5000)
