#include <cstdio>
#include <percy/percy.hpp>
#include <chrono>

#define MAX_TESTS 256

using namespace percy;
using kitty::dynamic_truth_table;

int main(){

    auto set_tt =  generate_npn_classes<4>();
    auto count = 0u;

    

    for(auto& tt : set_tt){
        kitty::dynamic_truth_table dtt(4);
        kitty::create_from_hex_string(dtt, kitty::to_hex(tt));
        mig mig;
        spec spec;
        bsat_wrapper solver;
        mig_encoder encoder(solver);
        spec[0] = dtt;

        auto res = mig_synthesize(spec, mig, solver, encoder);
        const auto sim_tts = mig.simulate();

        assert (sim_tts[0] == dtt);
        assert (mig.get_nr_inputs() == 4);
       // assert (mig.satisfies_spec( spec ) == true);

        std::cout << "Truth Table: " << kitty::to_hex(tt) << std::endl;
        std::cout << "Number of gates: " <<mig.get_nr_steps() << std::endl;
        //if (++count >= 10) break;
    }

return 0;
}


