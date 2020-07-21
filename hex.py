import sys
# Read the file and load it into a string
filepath = sys.argv[1]
f = open(filepath, 'r')
st = f.read()
# Convert the string to binary
bin_data = ' '.join(format(ord(x), 'b') for x in st)
# Display the string
print bin_data
