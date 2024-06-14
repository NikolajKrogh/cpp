import pandas as pd
import matplotlib.pyplot as plt
import os

"""
------------------  Exercise 6 ------------------
"""


def plot_example(file_path):
    # Load the data
    data = pd.read_csv(file_path)

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(data['Time'], data['A'], label='A', color='red')
    plt.plot(data['Time'], data['B'], label='B', color='green')
    plt.plot(data['Time'], data['C'], label='C', color='blue')

    # Add labels and title
    plt.xlabel('Time')
    plt.ylabel('Count')
    plt.title('Graph from CSV data: ' + file_path)
    plt.legend()

    # Ensure the directory exists
    graphs_dir = 'images/'
    if not os.path.exists(graphs_dir):
        os.makedirs(graphs_dir)

    # Save the plot to a PNG file
    plt.savefig('images/' + file_path.split('/')[-1].replace('.csv', '') + '.png', format='png')


def plot_circadian_rhythm(file_path):
    # Load the data
    data = pd.read_csv(file_path)

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(data['Time'], data['A'], label='A', color='red')
    plt.plot(data['Time'], data['C'], label='C', color='green')
    # plt.plot(data['Time'], data['DA'], label='DA', color='gray')
    # plt.plot(data['Time'], data['DR'], label='DR', color='purple')
    # plt.plot(data['Time'], data['D_A'], label='D_A', color='orange')
    # plt.plot(data['Time'], data['D_R'], label='D_R', color='yellow')
    # plt.plot(data['Time'], data['MA'], label='MA', color='pink')
    # plt.plot(data['Time'], data['MR'], label='MR', color='brown')
    plt.plot(data['Time'], data['R'], label='R', color='blue')

    # Add labels and title
    plt.xlabel('Time')
    plt.ylabel('Count')
    plt.title('Circadian Rhythm from CSV data: ' + file_path)
    plt.legend()

    # Ensure the directory exists
    graphs_dir = 'images/'
    if not os.path.exists(graphs_dir):
        os.makedirs(graphs_dir)

    # Save the plot to a PNG file
    plt.savefig('images/' + file_path.split('/')[-1].replace('.csv', '') + '.png', format='png')


def plot_covid19(file_path):
    # Load the data
    data = pd.read_csv(file_path)

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(data['Time'], data['S'], label='S', color='red')
    plt.plot(data['Time'], data['E'], label='E', color='green')
    plt.plot(data['Time'], data['I'], label='I', color='blue')
    plt.plot(data['Time'], data['H'], label='H', color='turquoise')
    plt.plot(data['Time'], data['R'], label='R', color='purple')

    # Add labels and title
    plt.xlabel('Time')
    plt.ylabel('Values')
    plt.title('COVID-19 Data from CSV: ' + file_path)
    plt.legend()

    # Ensure the directory exists
    graphs_dir = 'images/'
    if not os.path.exists(graphs_dir):
        os.makedirs(graphs_dir)

    # Save the plot to a PNG file
    plt.savefig('images/' + file_path.split('/')[-1].replace('.csv', '') + '.png', format='png')


def main():
    # Call the function for each file
    plot_example('CsvFiles/Example 1.csv')
    plot_example('CsvFiles/Example 2.csv')
    plot_example('CsvFiles/Example 3.csv')
    plot_circadian_rhythm('CsvFiles/Circadian Rhythm.csv')
    plot_covid19('CsvFiles/COVID19 SEIHR_10000.csv')


if __name__ == "__main__":
    main()
