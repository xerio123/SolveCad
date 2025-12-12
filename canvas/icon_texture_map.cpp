#include "icon_texture_map.hpp"
#include "icon_texture_id.hpp"
namespace dune3d::IconTexture {
const std::map<IconTextureID, Position> icon_texture_map = {
{ IconTextureID::CONSTRAINT_POINTS_COINCIDENT, { 0, 0 } },
{ IconTextureID::CONSTRAINT_HORIZONTAL, { 1, 0 } },
{ IconTextureID::CONSTRAINT_VERTICAL, { 2, 0 } },
{ IconTextureID::CONSTRAINT_PARALLEL, { 3, 0 } },
{ IconTextureID::CONSTRAINT_EQUAL_LENGTH, { 4, 0 } },
{ IconTextureID::CONSTRAINT_POINT_ON_LINE, { 5, 0 } },
{ IconTextureID::CONSTRAINT_MIDPOINT, { 0, 1 } },
{ IconTextureID::CONSTRAINT_WORKPLANE_NORMAL, { 1, 1 } },
{ IconTextureID::CONSTRAINT_SAME_ORIENTATION, { 2, 1 } },
{ IconTextureID::CONSTRAINT_POINT_ON_CIRCLE, { 3, 1 } },
{ IconTextureID::CONSTRAINT_ARC_ARC_TANGENT, { 4, 1 } },
{ IconTextureID::CONSTRAINT_ARC_LINE_TANGENT, { 5, 1 } },
{ IconTextureID::CONSTRAINT_PERPENDICULAR, { 0, 2 } },
{ IconTextureID::CONSTRAINT_POINT_IN_PLANE, { 1, 2 } },
{ IconTextureID::CONSTRAINT_LOCK_ROTATION, { 2, 2 } },
{ IconTextureID::CONSTRAINT_SYMMETRIC_HORIZONTAL, { 3, 2 } },
{ IconTextureID::CONSTRAINT_SYMMETRIC_VERTICAL, { 4, 2 } },
{ IconTextureID::CONSTRAINT_SYMMETRIC_LINE, { 5, 2 } },
{ IconTextureID::CONSTRAINT_BEZIER_BEZIER_TANGENT_SYMMETRIC, { 0, 3 } },
{ IconTextureID::CONSTRAINT_POINT_ON_BEZIER, { 1, 3 } },
{ IconTextureID::POINT_BOX, { 2, 3 } },
{ IconTextureID::POINT_CIRCLE, { 3, 3 } },
{ IconTextureID::POINT_DIAMOND, { 4, 3 } },
{ IconTextureID::POINT_CROSS, { 5, 3 } },
{ IconTextureID::POINT_TRIANGLE_DOWN, { 0, 4 } },
{ IconTextureID::CONSTRAINT_G2, { 1, 4 } },
};
const unsigned int icon_size = 16;
const unsigned int icon_border = 2;
}
