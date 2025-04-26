
r_intensity = 1
g_intensity = 1
b_intensity = 1

input_range = 64
output_range = 256
gamma_value = 2.1

base_gamma = [int((x / input_range) ** (gamma_value) * output_range) for x in range(input_range)]


gamma_r = [int(r_intensity * x) for x in base_gamma]
gamma_g = [int(g_intensity * x) for x in base_gamma]
gamma_b = [int(b_intensity * x) for x in base_gamma]

# detect the max value for each channel to determine the data type
datatype = 'uint8_t'
if max(gamma_r) > 255 or max(gamma_g) > 255 or max(gamma_b) > 255:
	datatype = 'uint16_t'


with open('gamma_py.h', 'w') as f:
    f.write('const '+datatype+' PROGMEM gamma_r[] = {\n')
    for i in range(0, len(gamma_r), 16):
        f.write(','.join([f'{str(x).rjust(5)}' for x in gamma_r[i:i+16]]) + ',\n')
    f.write('};\n')

    f.write('const '+datatype+' PROGMEM gamma_g[] = {\n')
    for i in range(0, len(gamma_g), 16):
        f.write(','.join([f'{str(x).rjust(5)}' for x in gamma_g[i:i+16]]) + ',\n')
    f.write('};\n')

    f.write('const '+datatype+' PROGMEM gamma_b[] = {\n')
    for i in range(0, len(gamma_b), 16):
        f.write(','.join([f'{str(x).rjust(5)}' for x in gamma_b[i:i+16]]) + ',\n')
    f.write('};\n')

