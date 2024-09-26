import argparse
import functools
import re


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--font', help='Path to font file')
    parser.add_argument('--output', help='Path to output file')
    args = parser.parse_args()

    with open(args.font) as font:
        src = font.read().lstrip()
        result = []
        BITMAP_PATTERN = re.compile(r'([.*@]+)')

        for line in src.splitlines():
            match = BITMAP_PATTERN.match(line)
            if not match:
                continue

            bits = [(0 if c == '.' else 1) for c in match.group(1)]
            bits_int = functools.reduce(lambda x, y: x * 2 + y, bits)
            result.append(bits_int.to_bytes(1, byteorder='little'))

        with open(args.output, 'wb') as output:
            output.write(b''.join(result))


if __name__ == '__main__':
    main()
