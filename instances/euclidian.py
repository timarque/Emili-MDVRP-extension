def remove_last_two_elements(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    modified_lines = []
    for line in lines:
        elements = line.strip().split()  # Splitting by whitespace
        modified_line = ' '.join(elements[:-2])  # Joining all elements except the last two
        modified_lines.append(modified_line)

    with open(output_file, 'w') as f:
        f.write('\n'.join(modified_lines))

# Example usage:
input_file = '/home/tagotuga/Emili-MDVRP-extension/instances/input.txt'
output_file = '/home/tagotuga/Emili-MDVRP-extension/instances/test.txt'
remove_last_two_elements(input_file, output_file)

