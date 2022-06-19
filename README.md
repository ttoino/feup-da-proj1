# FEUP-DA-PROJ1

First project for the DA course unit at FEUP.

A company wants to create an electronic crowdsourcing platform for deliveries.
They hire couriers for the normal deliveries and they have a van for the express deliveries.
In this project, we should develop algorithms to optimize different scenarios, such as:

- Use the minimum couriers possible while delivering the maximum orders
- Maximize the profit
- Minimize the average delivery time

## Building

This project uses [cmake](https://cmake.org/). Assuming it's installed and properly setup, simply run `cmake -S . -B build` in this project's directory to generate the build system, then `cmake --build build` to actually build the project.

This will generate two binaries in the `build` directory, `da_proj1` and `da_proj1_no_ansi`, one that uses [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) and one that doesn't.

Additionally, documentation will also be generated in the `docs` folder. Run `git submodule init` then `git submodule update` then build again to get the documentation website looking fancy.

## Running

Simply run the executable generated in the last section.

The UI is quite simple and self descriptive. You are presented with options to check the available vans and the orders to be delivered. You can also choose a
dataset to be load in the program and one of the scenarios mencioned above.

The program expects the [datasets](datasets) folder next to the current working directory. This can be changed in the [constants.hpp](includes/constants.hpp) file.

## Unit info

- **Name**: Desenho de Algoritmos (Algorithm Design)
- **Date**: Year 2, Semester 2, 2021/22
- **See also**: [feup-da](https://github.com/Naapperas/feup-da), [feup-da-proj2](https://github.com/Naapperas/feup-da-proj2)
- [**More info**](https://sigarra.up.pt/feup/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=484424)

## Disclaimer

This repository (and all others with the name format `feup-*`) are for archival and educational purposes only.

If you don't understand some part of the code or anything else in this repo, feel free to ask (although I may not understand it myself anymore).

Keep in mind that this repo is public. If you copy any code and use it in your school projects you may be flagged for plagiarism by automated tools.
