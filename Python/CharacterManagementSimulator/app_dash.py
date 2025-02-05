from flask import Flask
from dash import Dash, dcc, html, Input, Output, State, dash_table
import dash
import dash_bootstrap_components as dbc
from Simulator import Simulator


# Flask 서버 생성
server = Flask(__name__)

# Dash 앱 초기화
app = Dash(__name__, server=server, external_stylesheets=[dbc.themes.BOOTSTRAP])

# Excel 파일 경로
EXCEL_FILE = "Python/BattleSimulator/sample.xlsx"
simulator = Simulator(EXCEL_FILE)

initial_data = [{
    "name": char.name,
    "hp": char.hp,
    "defense": char.defense,
    "attack": char.attack,
    "speed": char.speed,
    "crit_rate": char.crit_rate,
    "crit_damage": char.crit_damage,
    "accuracy": char.accuracy,
    "dodge": char.dodge,
    "combat_power": char.combat_power
} for char in simulator.characters]

# Dash Layout
app.layout = dbc.Container([
    html.H1("Character Management System", className="text-center my-4"),
    
    dbc.Row([
        dbc.Col([
            html.H2("Character List"),
            dash_table.DataTable(
                id='character-table',
                columns=[
                    {"name": "Name", "id": "name"},
                    {"name": "HP", "id": "hp"},
                    {"name": "Defense", "id": "defense"},
                    {"name": "Attack", "id": "attack"},
                    {"name": "Speed", "id": "speed"},
                    {"name": "Crit Rate", "id": "crit_rate"},
                    {"name": "Crit Damage", "id": "crit_damage"},
                    {"name": "Accuracy", "id": "accuracy"},
                    {"name": "Dodge", "id": "dodge"},
                    {"name": "Combat Power", "id": "combat_power"},
                ],
                data=initial_data,
                style_table={'overflowX': 'auto'},
                style_cell={'textAlign': 'center'},
                page_size=10
            )
        ], width=7),
        
        dbc.Col([
            html.H2("Add Character"),
            dbc.Form([
                dbc.Input(id="name-input", placeholder="Name", type="text", className="mb-2"),
                dbc.Input(id="hp-input", placeholder="HP", type="number", className="mb-2"),
                dbc.Input(id="defense-input", placeholder="Defense", type="number", className="mb-2"),
                dbc.Input(id="attack-input", placeholder="Attack", type="number", className="mb-2"),
                dbc.Input(id="speed-input", placeholder="Speed", type="number", className="mb-2"),
                dbc.Input(id="crit-rate-input", placeholder="Crit Rate", type="number", min=0, max=1, step=0.01, className="mb-2"),
                dbc.Input(id="crit-damage-input", placeholder="Crit Damage", type="number", min=1, max=2, step=0.01, className="mb-2"),
                dbc.Input(id="accuracy-input", placeholder="Accuracy", type="number", min=0, max=1, step=0.01, className="mb-2"),
                dbc.Input(id="dodge-input", placeholder="Dodge", type="number", min=0, max=1, step=0.01, className="mb-2"),
                dbc.Button("Add Character", id="add-btn", color="primary", className="mb-2"),
            ]),
            html.Div(id="add-output")
        ], width=5)
    ], className="mb-4"),
    
    dbc.Row([
        dbc.Col([
            html.H2("Visualization"),
            dcc.Graph(id="combat-power-chart", figure=simulator.visualize_combat_power())
        ], width=6), 

        dbc.Col([
            html.H2(" "),
            dcc.Graph(id="win_probabilities-chart", figure=simulator.visualize_win_probabilities())
        ], width=6)
    ])
])

# Callbacks
@app.callback(
    Output('character-table', 'data'),
    Output('combat-power-chart', 'figure'),
    Output('win_probabilities-chart', 'figure'),
    Input('add-btn', 'n_clicks'),
    State('name-input', 'value'),
    State('hp-input', 'value'),
    State('defense-input', 'value'),
    State('attack-input', 'value'),
    State('speed-input', 'value'),
    State('crit-rate-input', 'value'),
    State('crit-damage-input', 'value'),
    State('accuracy-input', 'value'),
    State('dodge-input', 'value'),
    prevent_initial_call=True
)
def add_character_and_update_table(n_clicks, name, hp, defense, attack, speed, crit_rate, crit_damage, accuracy, dodge):
    if name and hp and defense and attack and speed and crit_rate and crit_damage and accuracy and dodge:
        if not (0 <= crit_rate <= 1):
            return dash.no_update, dash.no_update, "Crit Rate must be between 0 and 1."
        if not (0 <= crit_damage <= 2):
            return dash.no_update, dash.no_update, "Crit Damage must be between 0 and 2."
        if not (0 <= accuracy <= 1):
            return dash.no_update, dash.no_update, "Accuracy must be between 0 and 1."
        if not (0 <= dodge <= 1):
            return dash.no_update, dash.no_update, "Dodge must be between 0 and 1."

        simulator.add_character(name, float(hp), float(defense), float(attack), float(speed), 
                                float(crit_rate), float(crit_damage), float(accuracy), float(dodge))
        characters = simulator.characters
        
        table_data = [{
            "name": char.name,
            "hp": char.hp,
            "defense": char.defense,
            "attack": char.attack,
            "speed": char.speed,
            "crit_rate": char.crit_rate,
            "crit_damage": char.crit_damage,
            "accuracy": char.accuracy,
            "dodge": char.dodge,
            "combat_power": char.combat_power
        } for char in characters]
        
        combat_fig = simulator.visualize_combat_power()
        win_pro_fig = simulator.visualize_win_probabilities()

        return table_data, combat_fig, win_pro_fig
    return dash.no_update, dash.no_update


if __name__ == "__main__":
    # app.run(debug=True)
    app.run(host='0.0.0.0', port=5000)