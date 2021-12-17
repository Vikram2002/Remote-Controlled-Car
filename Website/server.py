from flask import Flask, render_template, url_for, jsonify, request
import os


app = Flask(__name__)


@app.route("/")
def home():
	return render_template('index.html')

@app.route("/desktop")
def desktop():
	return render_template('desktop.html')

@app.route("/mobile")
def mobile():
	return render_template('mobile.html')


@app.route('/pass_val',methods=['POST'])
def pass_val():
    name=request.args.get('value')
    print(name)
    save_Var(name)
    return jsonify({'reply':'success'})

def save_Var(variable):
	f = open("Instructions.txt", "w")
	f.writelines(variable)
	f.close()

if __name__ == '__main__':
	app.run(host = '0.0.0.0', debug = False)
