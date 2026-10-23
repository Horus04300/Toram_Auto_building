"""Replay a JSON statting input offline: python tools/statting/simulate.py input.json."""
import argparse
import json
from pathlib import Path
from native_model import Model, verify_evidence

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('input', type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    verify_evidence()
    result = Model().replay(json.loads(args.input.read_text(encoding='utf8')))
    data = json.dumps(result, ensure_ascii=False, indent=2)+'\n'
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(data, encoding='utf8')
    else:
        print(data)
