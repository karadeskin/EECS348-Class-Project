import csv
import os
import requests as re

if __name__ == '__main__':
    with open('test_inputs.txt') as tests:
        csv = csv.reader(tests)
        for row in csv:
            if os.system(f'./Calculator {row[0]}') != int(row[1]):
                print(f'failed test: {row[0]}')

    if website is running:
        re.post('http://127.0.0.1', data=row[0])
