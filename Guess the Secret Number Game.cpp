#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>  // For generating random numbers
#include <ctime>    // For time-based seed
using namespace std;

// Function to heapify a subtree rooted at index i (for Min-Heap)
void heapifyMin(vector<int>& heap, int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // Check if left child is smaller than root
    if (left < n && heap[left] < heap[smallest])
        smallest = left;

    // Check if right child is smaller than smallest so far
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    // If the smallest is not the root, swap and continue heapifying
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyMin(heap, n, smallest); // Recursively heapify the affected subtree
    }
}

// Function to heapify a subtree rooted at index i (for Max-Heap)
void heapifyMax(vector<int>& heap, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // Check if left child is larger than root
    if (left < n && heap[left] > heap[largest])
        largest = left;

    // Check if right child is larger than largest so far
    if (right < n && heap[right] > heap[largest])
        largest = right;

    // If the largest is not the root, swap and continue heapifying
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyMax(heap, n, largest); // Recursively heapify the affected subtree
    }
}

// Function to insert an element into the Min-Heap
void insert(vector<int>& heap, int value) {
    heap.push_back(value); // Add the new value at the end
    int i = heap.size() - 1; // Get the index of the new element

    // Move the new element up to restore the Min-Heap property
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]); // Swap with parent
        i = (i - 1) / 2; // Move to parent index
    }
}

// Function to remove the smallest element (root) from the Min-Heap
void removeMin(vector<int>& heap) {
    if (heap.empty()) { // Check if the heap is empty
        cout << "Heap is empty! Nothing to remove." << endl;
        return;
    }
    cout << "Removing smallest guess: " << heap[0] << endl; // Print the smallest element
    heap[0] = heap.back(); // Replace root with the last element
    heap.pop_back(); // Remove the last element
    heapifyMin(heap, heap.size(), 0); // Restore the Min-Heap property
}

// Function to print the current heaps and original numbers
void printHeaps(const vector<int>& original, const vector<int>& minHeap) {
    vector<int> maxHeap = original; // Create a copy for Max-Heap

    // Build Max-Heap from the original input
    int n = maxHeap.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMax(maxHeap, n, i); // Heapify the Max-Heap
    }

    cout << "Original inputted numbers: ";
    for (int val : original)
        cout << val << " ";
    cout << endl;

    cout << "Current Min-Heap: ";
    for (int val : minHeap)
        cout << val << " ";
    cout << endl;

    cout << "Current Max-Heap: ";
    for (int val : maxHeap)
        cout << val << " ";
    cout << endl;
}

// Function to generate a random secret number within a range
int generateSecretNumber(int minRange, int maxRange) {
    return rand() % (maxRange - minRange + 1) + minRange; // Generate random number in the range
}

// Main function containing the game logic
int main() {
    srand(time(0)); // Seed the random number generator
    vector<int> minHeap; // Min-Heap to store player guesses
    vector<int> originalInput; // Store original inputted numbers
    int minRange = 1, maxRange = 100; // Define the range for the secret number
    int secretNumber = generateSecretNumber(minRange, maxRange); // Generate the secret number
    int choice, guess; // Variables to store user input
    int maxGuesses = 5; // Maximum number of guesses per round
    int currentGuesses = 0; // Counter for guesses
    bool playAgain = true; // Flag to control the game loop

    // Introduction and instructions
    cout << "Welcome to Guess the Secret Number Game!" << endl;
    cout << "Can you guess the secret number between " << minRange << " and " << maxRange << "?" << endl;
    cout << "Use the Min-Heap to assist in your guessing!" << endl;

    do {
        // Display menu options
        cout << "\nMenu:" << endl;
        cout << "1. Start guessing the secret number" << endl;
        cout << "2. Remove the smallest guess from the heap" << endl;
        cout << "3. Display the original numbers, Min-Heap, and Max-Heap" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice; // Read user's choice

        switch (choice) {
        case 1: // Start guessing the secret number
            currentGuesses = 0;
            secretNumber = generateSecretNumber(minRange, maxRange); // Generate a new secret number

            cout << "\nStart guessing! You have " << maxGuesses << " chances." << endl;

            while (currentGuesses < maxGuesses) {
                cout << "Enter your guess: ";
                cin >> guess;
                originalInput.push_back(guess); // Store in the original input vector
                insert(minHeap, guess); // Insert the guess into the heap
                cout << "You added the guess: " << guess << endl;
                currentGuesses++;

                // Check if the guess matches the secret number
                if (guess == secretNumber) {
                    cout << "Congratulations! You've guessed the secret number!" << endl;
                    break; // Exit the guessing loop
                }
                // Provide hints based on the guess
                else if (guess < secretNumber) {
                    cout << "Hint: The secret number is larger than " << guess << "." << endl;
                    cout << "Hint: The secret number is between " << guess + 1 << " and " << maxRange << "." << endl;
                } else {
                    cout << "Hint: The secret number is smaller than " << guess << "." << endl;
                    cout << "Hint: The secret number is between " << minRange << " and " << guess - 1 << "." << endl;
                }

                // If the player reaches max guesses without success
                if (currentGuesses >= maxGuesses && guess != secretNumber) {
                    cout << "Sorry, you've reached the maximum number of guesses!" << endl;
                    cout << "The secret number was: " << secretNumber << endl;
                }
            }
            break;

        case 2: // Remove the smallest guess
            removeMin(minHeap);
            break;

        case 3: // Display the heaps and original numbers
            printHeaps(originalInput, minHeap);
            break;

        case 4: // Quit the game
            cout << "Thanks for playing! Goodbye!" << endl;
            break;

        default: // Handle invalid input
            cout << "Invalid choice. Please try again." << endl;
        }

        

    } while (choice != 4); // Repeat until the user chooses to quit

    return 0;
}