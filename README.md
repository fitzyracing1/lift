# lift

lift is a header-only C++ file, `internet-as-model.hpp`, that treats the internet (or a specific URL) as an `ai::Model`. It includes its own copy of the `ai::Model` base (same interface as [focus](https://github.com/fitzyracing1/focus)'s `ai-iface.hpp`) and adds `class InternetModel : public Model`, constructed with an endpoint string.

**Status:** `InternetModel::infer` is a **stub**. It returns a text message naming the target and prompt and says "stub – replace with real network call". The source has a `TODO: real HTTP / agent call goes here`, and no networking code exists yet.

## Getting started

```cpp
#include "internet-as-model.hpp"
ai::InternetModel m("https://example.com");
std::string out = m.infer("hello");   // stub output
```

It needs only standard headers. `index.html` is the project page. The repo had no README before this docs commit, and it has no tests and no LICENSE file.

Copyright (c) 2026 Joshua Almeida

## Documentation

- In-repo docs: [docs/](docs/index.md)
- Wiki: [https://github.com/fitzyracing1/lift/wiki](https://github.com/fitzyracing1/lift/wiki)

## Plans

This project is free, and its license stays as is. Support it through [GitHub Sponsors](https://github.com/sponsors/fitzyracing1):

- **Free**: use the code, community support.
- **Pro ($49/month)**: priority issues and support.
- **Team ($199/month)**: priority support for your team plus early access.
