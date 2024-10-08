#include <filesystem>
#include <fstream>

#include "IntegrationTestSuite.hpp"

void IntegrationTestSuite::SetUp() {
  std::filesystem::create_directories(kTestDir);
  std::ofstream file1(kTestDir + "/file1");
  std::ofstream file2(kTestDir + "/file2");
  std::ofstream file3(kTestDir + "/file3");
  file1 << "[Chorus]\n"
           "A well a everybody's heard about the bird\n"
           "B-b-b bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, the bird is the word\n"
           "A well a bird, bird, bird, well the bird is the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, well the bird is the word\n"
           "A well a bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, well the bird is the word\n"
           "A well a bird, bird, b-bird's the word\n"
           "\n"
           "[Refrain]\n"
           "A well a don't you know about the bird?\n"
           "Well, everybody knows that the bird is the word!\n"
           "A well a bird, bird, b-bird's the word\n"
           "A well a\n"
           "\n"
           "[Chorus]\n"
           "A well a everybody's heard about the bird\n"
           "Bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "A well a bird, bird, bird, b-bird's the word\n"
           "You might also like\n"
           "Big Foot (A Cappella)\n"
           "Nicki Minaj\n"
           "THE HEART PART 6\n"
           "Drake\n"
           "Family Matters\n"
           "Drake\n"
           "[Refrain]\n"
           "A well a don't you know about the bird?\n"
           "Well, everybody's talking about the bird!\n"
           "A well a bird, bird, b-bird's the word\n"
           "A well a bird\n"
           "\n"
           "[Break]\n"
           "Surfin' bird\n"
           "B-b-b aah, aah!\n"
           "Pa pa pa pa, pa pa pa pa, pa pa pa pa, pa pa pa pa\n"
           "Pa pa pa pa, pa pa pa pa, pa pa pa pa\n"
           "Ooma mow mow, papa, ooma mow mow\n"
           "\n"
           "[Bridge]\n"
           "Papa ooma mow mow, papa ooma mow mow\n"
           "Papa ooma mow mow, papa ooma mow mow\n"
           "Ooma mow mow, papa ooma mow mow\n"
           "Papa ooma mow mow, papa ooma mow mow\n"
           "Papa ooma mow mow, papa ooma mow mow\n"
           "Oom oom oom oom, ooma mow mow\n"
           "Papa ooma mow mow, papa oom oom oom\n"
           "Oom ooma mow mow, papa ooma mow mow\n"
           "Ooma mow mow, papa ooma mow mow\n"
           "Papa a mow mow, papa ooma mow mow\n"
           "Papa ooma mow mow, ooma mow mow\n"
           "Papa ooma mow mow, ooma mow mow\n"
           "Papa oom oom oom oom, ooma mow mow\n"
           "Oom oom oom oom, ooma mow mow\n"
           "Ooma mow mow, papa ooma mow mow\n"
           "Papa ooma mow mow, ooma mow mow\n"
           "[Refrain]\n"
           "Well a don't you know about the bird?\n"
           "Well, everybody knows that the bird is the word!\n"
           "A well a bird, bird, b-bird's the word\n"
           "\n"
           "[Outro]\n"
           "A well a ooma mow mow\n"
           "Papa ooma mow mow\n"
           "Papa ooma mow mow\n"
           "Papa ooma mow mow\n"
           "Papa ooma mow mow\n"
           "Papa ooma mow mow\n"
           "Papa ooma mow mow" << std::endl;
  file2 << "Quintus Horatius Flaccus\n"
           "HORATII CARMINUM III, 30\n"
           "  \"Ad Melpomenen\"\n"
           "\n"
           "Exegi monumentum aere perennius\n"
           "Regalique situ pyramidum altius,\n"
           "Quod non imber edax, non aquilo impotens\n"
           "Possit diruere aut innumerabilis\n"
           "\n"
           "Annorum series et fuga temporum.\n"
           "Non omnis moriar multaque pars mei\n"
           "Vitabit Libitinam: usque ego postera\n"
           "Crescam laude recens, dum Capitolium\n"
           "\n"
           "Scandet cum tacita virgine pontifex:\n"
           "Dicar, qua violens obstrepit Aufidus\n"
           "Et qua pauper aquae Daunus agrestium\n"
           "Regnavit populorum, ex humili potens\n"
           "\n"
           "Princeps Aeolium carmen ad Italos\n"
           "Deduxisse modos. Sume superbiam\n"
           "Quaesitam meritis et mihi Delphica\n"
           "Lauro cinge volens, Melpomene, comam." << std::endl;
  file3 << "Peccatum\n"
           "Cantatum\n"
           "Extatum et oratum\n"
           "Peccatum extatum\n"
           "Nomine patrum\n"
           "Nomine partum\n"
           "\n"
           "Call the sons of Acheron\n"
           "The leaders of Iesaia\n"
           "All the hordes of Babylon\n"
           "The heretics who praise the lier\n"
           "Brothers of Tiberius\n"
           "The reign of blood and fire\n"
           "Sanctify the virgin son\n"
           "The prophet of the bible choir\n"
           "\n"
           "Run far from the sun\n"
           "War has begun\n"
           "Into the final fire\n"
           "Run far from the sun\n"
           "Into the eye of the storm\n"
           "\n"
           "Peccatum\n"
           "Cantatum\n"
           "Extatum et oratum\n"
           "Peccatum extatum\n"
           "Nomine patrum\n"
           "Nomine partum\n"
           "You might also like\n"
           "Higher Than Heaven\n"
           "Powerwolf\n"
           "Coleus Sanctus\n"
           "Powerwolf\n"
           "All We Need Is Blood\n"
           "Powerwolf\n"
           "Saw the rites of Golgotha\n"
           "The torment of your trial\n"
           "Crucify the fallen son\n"
           "The sacrament before denial\n"
           "Brothers of Samaria\n"
           "The armaments of Tyre\n"
           "Sent to burn the holy one\n"
           "Born to set the world on fire\n"
           "\n"
           "Run far from the sun\n"
           "War has begun\n"
           "Into the final fire\n"
           "Run far from the sun\n"
           "Into the eye of the storm\n"
           "\n"
           "Peccatum\n"
           "Cantatum\n"
           "Extatum et oratum\n"
           "Peccatum extatum\n"
           "Nomine patrum\n"
           "Nomine partum" << std::endl;
  file1.close();
  file2.close();
  file3.close();
  ASSERT_EQ(indexer_.CreateIndex(), 0);
}

void IntegrationTestSuite::TearDown() {
  std::filesystem::remove_all(kTestDir);
}
