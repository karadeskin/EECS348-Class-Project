import csv
import subprocess
# import requests as re

WEB_URL = 'http://137.184.123.158:3000/'

if __name__ == '__main__':
    with open('test_cases.csv') as tests:
        csvfile = csv.reader(tests)
        for row in csvfile:
            result = subprocess.run(f'./CalculatorStandalone "{row[0]}"', shell=True, stdout=subprocess.PIPE, text=True)
            if result.stdout.strip() != row[1].strip():
                print(f'failed test {row[0]}: expected {row[1]}; got {result.stdout.strip()}')

    import requests as re
    with open('test_cases.csv') as tests:
        csvfile = csv.reader(tests)
        for row in csvfile:
            expr = {'expression': row[0]}
            response = re.post('http://137.184.123.158:3000/', json=expr)
            result = response.text
            if result.strip() != row[1].strip():
                print(f'failed web test {row[0]}: expected {row[1]}; got {result.strip()}')
