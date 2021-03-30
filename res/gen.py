import math

ll = [(1, 1), (1, -1), (-1, -1), (-1, -1), (-1, 1), (1, 1)]

if __name__ == '__main__':
    for i, j in ll:
        print(0.5 + i * 0.15, j * 0.45, 0, 0, 123)

    for i in range(400):
        alpha = math.pi / 400
        print(0.0, 0.5, 0, 0, 170)
        print(0.0 + 0.5 * math.cos(i * alpha), 0.5 + 0.5 * math.sin(i * alpha), 0, 0, 170)
        print(0.0 + 0.5 * math.cos((i + 1) * alpha), 0.5 + 0.5 * math.sin((i + 1) * alpha), 0, 0, 170)

    for i, j in ll:
        print(i * 0.5, j * 0.5, 0, 0, 170)

    for i, j in ll:
        print(-0.30 + i * 0.35, 0.25 + j * 0.225, 202, 202, 202)

