/*
* Authors: Daniel Nagy, Euan Robertson, Matthew Gallacher, Hamish Aitken, Lewis McLean
*/
#include "authlib.h"
#include "openssl/sha.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>


char c78ec02c7c1ab17de756ddf5d0ee9bddaddf0f96b35a5e0fc4da5f1702a45880[20];
char f16815e9166435d9f47b4af35aae33c5c6f0e23732cabe0980eab49bd75474a6[20];
int ccceb9b562178b1d0279cb2c5f985feb382e55090cb6e3af4a58525c542c04fa=0;

//borrowed from - https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
std::string abfcf3ac1e1e91cfd2bcc5d96d5e759f3e18416f4030eea48295c59087d215b2(const std::string& ecafec109732dde17f2dddbc5239d3bae6f0e9fa87e93a745ecf22e587b52702)
{
    unsigned char e7d2c5c168f86693473d2be563dd02acacd40997df5d1c77459149def155d650[SHA256_DIGEST_LENGTH];
    SHA256_CTX a61ab187602ea746e399f84c203348c3b69ea00035bc9e214c9c31cf6a5b9573;
    SHA256_Init(&a61ab187602ea746e399f84c203348c3b69ea00035bc9e214c9c31cf6a5b9573);
    SHA256_Update(&a61ab187602ea746e399f84c203348c3b69ea00035bc9e214c9c31cf6a5b9573, ecafec109732dde17f2dddbc5239d3bae6f0e9fa87e93a745ecf22e587b52702.c_str(), ecafec109732dde17f2dddbc5239d3bae6f0e9fa87e93a745ecf22e587b52702.size());
    SHA256_Final(e7d2c5c168f86693473d2be563dd02acacd40997df5d1c77459149def155d650, &a61ab187602ea746e399f84c203348c3b69ea00035bc9e214c9c31cf6a5b9573);
    std::stringstream d6ce25b18b9feb462bf16ff5e5613a496081c9f61bd97d31e559260a0c75bf04;
    for(unsigned char cd2484a3e697da45bc2123cc29372a92af8def01cfcec14fdd2d80cf8605a8e8 : e7d2c5c168f86693473d2be563dd02acacd40997df5d1c77459149def155d650)
    {
        d6ce25b18b9feb462bf16ff5e5613a496081c9f61bd97d31e559260a0c75bf04 << std::hex << std::setw(2) << std::setfill('0') << (int)cd2484a3e697da45bc2123cc29372a92af8def01cfcec14fdd2d80cf8605a8e8;
    }
    return d6ce25b18b9feb462bf16ff5e5613a496081c9f61bd97d31e559260a0c75bf04.str();
}
/*
 * This function authenticates a user.
 */
void b01c2962993f64f85cdbe3ddecdd2d69cd18a0d237b99e35c593a9960711e7f9() {

    std::ifstream c1c1dcc3cd0a854bd38361131e2d92fd890e0fc5f45f9c9f20ac82df8911503f("passwords.txt");
    std::string bc006be24b7944bdafb1b50736f3e7d93094776c3505a8e1328609960b640d3a;


    //search for username in the file
    if(c1c1dcc3cd0a854bd38361131e2d92fd890e0fc5f45f9c9f20ac82df8911503f.is_open()) {
        while (getline(c1c1dcc3cd0a854bd38361131e2d92fd890e0fc5f45f9c9f20ac82df8911503f, bc006be24b7944bdafb1b50736f3e7d93094776c3505a8e1328609960b640d3a)) {
            // if username is found in the file check password
            if (bc006be24b7944bdafb1b50736f3e7d93094776c3505a8e1328609960b640d3a.substr(0, bc006be24b7944bdafb1b50736f3e7d93094776c3505a8e1328609960b640d3a.find(':')) == c78ec02c7c1ab17de756ddf5d0ee9bddaddf0f96b35a5e0fc4da5f1702a45880 && bc006be24b7944bdafb1b50736f3e7d93094776c3505a8e1328609960b640d3a.find(
                    abfcf3ac1e1e91cfd2bcc5d96d5e759f3e18416f4030eea48295c59087d215b2(
                            f16815e9166435d9f47b4af35aae33c5c6f0e23732cabe0980eab49bd75474a6)) != std::string::npos) {
                // if password is correct, set ccceb9b562178b1d0279cb2c5f985feb382e55090cb6e3af4a58525c542c04fa to 1
                ccceb9b562178b1d0279cb2c5f985feb382e55090cb6e3af4a58525c542c04fa = 1;
            }
        }
    }
}
/*
 * This is the main function for the login program. Collects the username and password from the user and then calls the b01c2962993f64f85cdbe3ddecdd2d69cd18a0d237b99e35c593a9960711e7f9 function.
 */
int main() {
    printf("Enter username: ");
    scanf("%s", c78ec02c7c1ab17de756ddf5d0ee9bddaddf0f96b35a5e0fc4da5f1702a45880);

    printf("Enter password: ");
    scanf("%s", f16815e9166435d9f47b4af35aae33c5c6f0e23732cabe0980eab49bd75474a6);

    // authenticate user if b01c2962993f64f85cdbe3ddecdd2d69cd18a0d237b99e35c593a9960711e7f9 is successful
    b01c2962993f64f85cdbe3ddecdd2d69cd18a0d237b99e35c593a9960711e7f9();
    ccceb9b562178b1d0279cb2c5f985feb382e55090cb6e3af4a58525c542c04fa == 1 ? authenticated(std::string(c78ec02c7c1ab17de756ddf5d0ee9bddaddf0f96b35a5e0fc4da5f1702a45880)) : rejected(std::string(c78ec02c7c1ab17de756ddf5d0ee9bddaddf0f96b35a5e0fc4da5f1702a45880));
}