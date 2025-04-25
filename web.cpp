#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

emp::web::Document doc{"target"};
emp::Random random_2{5};
OrgWorld world{random_2};

class AEAnimator : public emp::web::Animate

{

    // arena width and height
    const int num_h_boxes = 10;
    const int num_w_boxes = 10;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

public:
    AEAnimator()
    {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        Organism *new_org = new Organism(&random_2);
        world.Inject(*new_org);
        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
    }

    void DoFrame() override
    {
        canvas.Clear();
        world.Update();

        // Draw the grid
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++)
        {
            for (int y = 0; y < num_h_boxes; y++)
            {
                if (world.IsOccupied(org_num))
                {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                }
                else
                {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() { animator.Step(); }