
from flask import Flask, render_template, request, redirect, url_for
from Simulator import Simulator, Character

app = Flask(__name__)

# Excel 파일 경로
EXCEL_FILE = "Python/BattleSimulator/sample.xlsx"

# Simulator 객체 초기화
simulator = Simulator(EXCEL_FILE)


@app.route('/')
def home():
    return render_template("home.html", characters=simulator.characters)


@app.route('/add', methods=['POST'])
def add_character():
    name = request.form['name']
    hp = float(request.form['hp'])
    defense = float(request.form['defense'])
    attack = float(request.form['attack'])
    speed = float(request.form['speed'])
    crit_rate = float(request.form['crit_rate'])
    crit_damage = float(request.form['crit_damage'])
    accuracy = float(request.form['accuracy'])
    dodge = float(request.form['dodge'])

    simulator.add_character(name, hp, defense, attack, speed, crit_rate, crit_damage, accuracy, dodge)
    return redirect(url_for('home'))


@app.route('/delete/<name>')
def delete_character(name):
    simulator.delete_character(name)
    return redirect(url_for('home'))


@app.route('/simulate')
def simulate():
    results = simulator.simulate_all_battles()
    return render_template("simulate.html", results=results)


@app.route('/visualize/combat_power')
def visualize_combat_power():
    simulator.visualize_combat_power()
    return redirect(url_for('home'))


@app.route('/visualize/win_probabilities')
def visualize_win_probabilities():
    simulator.visualize_win_probabilities()
    return redirect(url_for('home'))


if __name__ == '__main__':
    app.run(debug=True)
