from flask import Flask, render_template, send_from_directory

app = Flask(__name__)

# Route for serving files from the media folder
@app.route('/media/<path:filename>')
def media(filename):
    return send_from_directory('media', filename)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/contact')
def contact():
    return render_template('contact.html')

@app.route('/news')
def news():
    return render_template('news.html')

if __name__ == '__main__':
    app.run(debug=True)
