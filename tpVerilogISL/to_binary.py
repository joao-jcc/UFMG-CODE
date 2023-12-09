import sys

def text_to_binary(file_path, output_path):
    with open(file_path, 'r') as file:
        text_content = file.read()

    words = text_content.split()

    binary_strings = {'id':[], 'word':[], 'binary':[]}
    for i, word in enumerate(words):
        binary_strings['id'].append(i)
        binary_strings['word'].append(word)
        binary_strings['binary'].append(''.join(format(ord(char), '08b') for char in word))

    with open(output_path, 'w') as output_file:
        for word_id in binary_strings['id']:
            word = binary_strings['word'][word_id]
            binary = binary_strings['binary'][word_id]
            output_file.write("{},{},{}\n".format(word_id, word, binary))

if __name__ == '__main__':
    if (len(sys.argv) != 3):
        print("uso: python to_binary.py input_file output_file")
    
    else:
        text_to_binary(sys.argv[1], sys.argv[2])
        print("Sucess!")
