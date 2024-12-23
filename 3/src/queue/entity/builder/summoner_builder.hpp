#ifndef SUMMONER_BUILDER_HPP
#define SUMMONER_BUILDER_HPP

#include "queue/entity/summoner.hpp"

class SummonerBuilder {
  private:
    Summoner summoner_;

  public:
    explicit SummonerBuilder(Ability ability) : summoner_(ability) {}

    SummonerBuilder&
    max_energy(size_t energy) {
        summoner_.energy = energy;
        summoner_.max_energy = energy;
        return *this;
    }

    SummonerBuilder&
    accum_index(size_t index) {
        summoner_.accum_index = index;
        return *this;
    }

    Summoner
    build() {
        return std::move(summoner_);
    }
};

#endif // SUMMONER_BUILDER_HPP
