# NWT4 - Spectrum Analyser Software

NWT4 is a versatile and comprehensive software tool designed to work with the nwt4 and 35m-4400m spectrumanalysers. This software provides a user-friendly interface for conducting and visualizing spectrum analysis efficiently.

## Features

- **Support for NWT and 35m-4400m**: Fully compatible with the nwt4 and 35m-4400m spectrumanalyser boards.
- **Real-time Spectrum Analysis**: Conduct real-time analysis and view detailed spectrum graphs.
- **Frequency Range**: Capable of analysing a wide range of frequencies.
- **User-friendly Interface**: Easy-to-use interface designed for both professionals and hobbyists.
- **Data Export**: Export analysis results in various formats for further processing or reporting.
- **Customizable Settings**: Configure settings to suit your specific analysis needs.

## Installation

### Prerequisites

Before you begin, ensure you have the following software installed:

- Qt6
- CMake
- C++ Compiler (like GCC)

### Linux (Ubuntu)

1. **Clone the repository:**

    ```sh
    git clone https://github.com/chrisabit-it/nwt4.git
    cd nwt4
    ```

2. **Build the software:**

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the software:**

    ```sh
    ./nwt4
    ```

### Debian Package

To create a Debian package, follow these steps:

1. **Build the package:**

    ```sh
    cd build
    cpack
    ```

2. **Install the package:**

    ```sh
    sudo dpkg -i nwt4_<version>_amd64.deb
    ```

3. **Run the software:**

    ```sh
    nwt4
    ```

## Usage

1. Connect your spectrumanalyser (NWT or 35m-4400m) to your computer.
2. Start the NWT4 Software.
3. Configure the frequency range and analysis settings as needed.
4. Click the "Sweep" button to begin the spectrum analysis.
5. View the results in real time on the graph.

## Boards

The NWT4 software is rather ancient. A unknown amount of boards were developed.
Currently the focus seems to be on boards from China: 

[PCB](./doc/sa-35m-4400m_pcb.jpg)

The following applies to this board:

- Don't use NWT4's "Settings/Firmware Update"!
- If you want to backup/update the Firmware - use the onboard SWD connector accordingly! 
- "Frequency Multiplication" is set to Factor 10 on default. Don't change this value in the Settings.
- If you want to calibrate using "Sweep/Channel # Calibration":
  - you have to use the logarithmic mode! 
  - you have to insert a 40db attenuator between RFout an RFin
  - linear mode is not supported!

## Contributing

Contributions are welcome! Please read the [CONTRIBUTING.md](CONTRIBUTING.md) file for guidelines on how to contribute to this project.

**Please note**:

- The Software was originally developed using Qt4
- It has been ported by chrisabit-it@posteo.de using Qt6
- The software was _not_ developed by the project maintainer
- The software _not_ refactored. There is a _huge_ amount of code that can be optimised.
- The software was developed for the German amateur radio sector. Therefore, many code sections are written in German. 

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

The original developer and copyright owner is:
    
- Andreas Lindenau
- DL4JAL@darc.de

## Contact

If you have any questions, issues, or suggestions, please open an issue on GitHub or contact the project maintainer at [chrisabit-it@posteo.de](mailto:youremail@domain.com).

---

Thank you for using NWT4!