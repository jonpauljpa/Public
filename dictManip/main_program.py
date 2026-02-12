import re

resource_counts = {}
requestor_counts = {}
requestor_resources = {}

def extract_data():
    apache_log = open("access_log", 'r')
    parsed_data = r"^([0-9A-za-z.-]+).*?\"[A-Z-]+.*?(.*?)\"" # improved regex, using lazy quantifiers to remove non resource chars

    for line in apache_log.readlines():

        match = re.findall(parsed_data, line)

        tuple_data = match[0] # unpacking tuple from list, extracting data below
        requestor = tuple_data[0]
        resource_path = tuple_data[1]

        if resource_path in resource_counts: # counting dict logic for resource dict
            resource_counts[resource_path] += 1
        else:
            resource_counts[resource_path] = 1

        if requestor in requestor_counts: # counting dict logic for requestor dict
            requestor_counts[requestor] += 1
        else:
            requestor_counts[requestor] = 1

        if requestor not in requestor_resources: # init empty dict for nesting
            requestor_resources[requestor] = {}

        inner_dictionary = requestor_resources[requestor] # making sure not to slot this in the if statement above, populating inner dict

        if resource_path not in inner_dictionary: # init counter for inner dict
            inner_dictionary[resource_path] = 1
        else:
            inner_dictionary[resource_path] += 1

def most_accessed_resource(): # not returning a value as it wasn't specified

    most_accessed = "" # init string variable for requestor dict value
    path_count = 0 # init int variable for counting dict match

    for value in resource_counts:
        if resource_counts[value] > path_count:
            path_count = resource_counts[value] # counter is the value associated with key position
            most_accessed = value # path is literal key within key value pair

    print(f"\nMost Accessed Resource: {most_accessed}\nAccessed: {path_count} Times\n")

def top_requestor(): # print in func once more, probably bad practice

    top_requestor = ""
    request_count = 0

    for value in requestor_counts:
        if requestor_counts[value] > request_count:
            request_count = requestor_counts[value] # same logic as above func, using requestor counting dict
            top_requestor = value

    print(f"Top Requestor: {top_requestor}\nRequests Made: {request_count}\n")

def top_requestor_resource(): # copied top_requestor func into this, definitely bad practice


    top_requestor = ""
    request_count = 0

    for value in requestor_counts:
        if requestor_counts[value] > request_count:
            request_count = requestor_counts[value]
            top_requestor = value # grabbing the top requestor key value pair once more to access nested dict here


    max_requestor = top_requestor # declaring fstring vars, assigning top requestor literal key to var
    max_count = 0
    max_path = ""

    for key in requestor_resources:
        if key == max_requestor: # iterating thru to find top requestor key (keys() may be better here)
            inner_value = requestor_resources[key] # assign found key:value to var
            for x in inner_value: # iterating thru inner dict to sort by
                if inner_value[x] > max_count:
                    max_count = inner_value[x]
                    max_path = x

    print(f"Top Requestor: {max_requestor}\nMost Utilized Resource: {max_path}\nAccessed: {max_count} times.\n")


def summary_report(): # just calling funcs here with built in formatted prints

    most_accessed_resource()
    top_requestor()
    top_requestor_resource()


extract_data()
summary_report()



