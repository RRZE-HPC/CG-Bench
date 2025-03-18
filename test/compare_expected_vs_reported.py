import sys
import os  # import os module
import ast
import pprint

def compare_files(expected_file, reported_file):
	def compare_dicts_and_return_diff(expected, reported):
		diff = {}

		# Loop through each key in expected
		for key in expected:
			# Get the sub-dictionaries for the current key
			sub_expected = expected[key]
			sub_reported = reported.get(key, {})

			# Loop through the keys within each sub-dictionary (colInd, rowPtr, val)
			for sub_key in sub_expected:
				list1 = sub_expected[sub_key]
				list2 = sub_reported.get(sub_key, [])

				# If lists are different, record the difference in the diff dictionary
				if list1 != list2:
					if key not in diff:
						diff[key] = {}
					diff[key][sub_key] = {
						"expected": list1,
						"reported": list2
					}

		return diff
  
	with open(expected_file, 'r', encoding='utf-8') as f1, open(reported_file, 'r', encoding='utf-8') as f2:
		expected_unformatted = f1.readlines()
		reported_unformatted = f2.readlines()

		expected_formatted = {}
		reported_formatted = {}

		for line in expected_unformatted:
			if "On rank" in line:
				rank = int(line.split()[-1])
				if rank not in expected_formatted.keys():
					expected_formatted[rank] = {"rowPtr" : [], "colInd" : [], "val" : []}
					continue
			if "rowPtr" in line:
				expected_formatted[rank]["rowPtr"] = ast.literal_eval(line.split('rowPtr = ')[1].split('colInd')[0].strip())
			if "colInd" in line:
				expected_formatted[rank]["colInd"] = ast.literal_eval(line.split('colInd = ')[1].split('val')[0].strip())
			if "val" in line:
				expected_formatted[rank]["val"] = ast.literal_eval(line.split('val = ')[1].strip())
		
		for line in reported_unformatted:
			if "On rank" in line:
				rank = int(line.split()[-1])
				if rank not in reported_formatted.keys():
					reported_formatted[rank] = {"rowPtr" : [], "colInd" : [], "val" : []}
					continue
			if "rowPtr" in line:
				reported_formatted[rank]["rowPtr"] = ast.literal_eval(line.split('rowPtr = ')[1].split('colInd')[0].strip())
			if "colInd" in line:
				reported_formatted[rank]["colInd"] = ast.literal_eval(line.split('colInd = ')[1].split('val')[0].strip())
			if "val" in line:
				reported_formatted[rank]["val"] = ast.literal_eval(line.split('val = ')[1].strip())

		
		# pprint.pprint(expected_formatted)
		# pprint.pprint(reported_formatted)

		return compare_dicts_and_return_diff(expected_formatted, reported_formatted)


if __name__ == "__main__":

	dir = "results/expected/"

	for entry in os.scandir(dir):  
		if entry.is_file():
			file_name = os.path.basename(entry)
			print(f"Validating: {file_name}...")
			diff = compare_files(f"results/expected/{file_name}", f"results/reported/{file_name}")
			print("Errors: ", end='')
			pprint.pprint(diff)

