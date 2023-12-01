#include <iostream>
#include <map>
#include <mutex>
#include <thread>

std::mutex scoreMutex;
std::map<int, int> PlayerScores;

void UpdateScore(int playerId, int score) {
    std::lock_guard<std::mutex> guard(scoreMutex);
    PlayerScores[playerId] += score;
}

void PlayerThread(int playerId) {
    // Simulate updating the score multiple times
    for (int i = 0; i < 5; ++i) {
        UpdateScore(playerId, 10);
    }
}

int main() {
    std::jthread player1(PlayerThread, 1);
    std::jthread player2(PlayerThread, 2);

    // No need to call join(), as jthread does this automatically upon destruction

    // Print the final scores
    for (const auto& [playerId, score] : PlayerScores) {
        std::cout << "Player " << playerId << " Score: " << score << std::endl;
    }

    return 0;
}
