import csv
import pdb
import json
from pprint import pprint as pp

def read_csv_to_dict_with_key(file_path, key_column):
    data = {}
    with open(file_path, mode='r', encoding='utf-8') as file:
        csv_reader = csv.DictReader(file)
        for row in csv_reader:
            key = row[key_column]
            data[key] = dict(row)
    return data

# 사용 예시
file_path = 'someip_service_spec.csv'
key_column = 'SERVICE_NAME'  # 'name' 열을 키로 사용
csv_data = read_csv_to_dict_with_key(file_path, key_column)

with open('someip_service_spec.json', 'w') as file:
    json.dump(csv_data, file, indent=4)

pp(csv_data)
