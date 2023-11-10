from gtts import gTTS
from flask import Flask,Response,request, send_file
import os

app=Flask(__name__)

@app.route('/t2s', methods=['GET'])
def t2s():
    txt=request.args.get('txt')
    print(txt)
    tts = gTTS(txt)
    filepath='tmp/temp.mp3'
    if not os.path.exists('tmp'):
        os.makedirs('tmp')
    tts.save(filepath)
    return send_file(filepath)

if __name__=="__main__":
    print("\n-----------------------------------------------\n")
    print("usage: http://<url>/t2s?txt?=<your text>\n")
    print("-----------------------------------------------\n")
    app.run(debug=True, host='0.0.0.0', port=3000)
