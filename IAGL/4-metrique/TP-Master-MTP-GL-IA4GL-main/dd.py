import json

if __name__ == '__main__':
    data = r'"\u00d8\u00b5\u00d9\u0086\u00d8\u00a7\u00d8\u00b9\u00d8\u00a9 \u00d8\u00a7\u00d9\u0084\u00d8\u00a7\u00d9\u0085\u00d9\u0088\u00d8\u00a7\u00d8\u00ac \u00f0\u009f\u00a4\u00af\u00f0\u009f\u00a4\u00af\u00f0\u009f\u0098\u0082"'
    print(json.loads(data).encode('latin1').decode('utf8'))