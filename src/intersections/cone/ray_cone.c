#include "../../../inc/miniRT.h"

static void	cone_side_init(t_cone_side *cs, t_ray ray, t_cone *cone)
{
    cs->w = vec3_subtract(ray.origin, cone->apex);
    cs->k = cone->radius / cone->height;
    cs->k2 = cs->k * cs->k;
    cs->dv = vec3_dot(ray.direction, cone->axis);
    cs->wv = vec3_dot(cs->w, cone->axis);
    cs->d_perp = vec3_subtract(ray.direction, vec3_scale(cone->axis, cs->dv));
    cs->w_perp = vec3_subtract(cs->w, vec3_scale(cone->axis, cs->wv));
    cs->a = vec3_dot(cs->d_perp, cs->d_perp) - cs->k2 * cs->dv * cs->dv;
    cs->b = 2.0 * (vec3_dot(cs->w_perp, cs->d_perp)
            - cs->k2 * cs->wv * cs->dv);
    cs->c = vec3_dot(cs->w_perp, cs->w_perp) - cs->k2 * cs->wv * cs->wv;
}

static bool	cone_side_solve(t_cone_side *cs)
{
    cs->disc = cs->b * cs->b - 4.0 * cs->a * cs->c;
    if (fabs(cs->a) < EPSILON || cs->disc < 0.0)
        return (false);
    cs->sqrt_disc = sqrt(cs->disc);
    cs->t0 = (-cs->b - cs->sqrt_disc) / (2.0 * cs->a);
    cs->t1 = (-cs->b + cs->sqrt_disc) / (2.0 * cs->a);
    if (cs->t0 > cs->t1)
    {
        cs->sqrt_disc = cs->t0;
        cs->t0 = cs->t1;
        cs->t1 = cs->sqrt_disc;
    }
    return (true);
}

static bool	cone_side_hit(t_ray ray, t_cone *cone, double *t_hit)
{
    t_cone_side	cs;
    double		m;

    if (!cone || !t_hit)
        return (false);
    cone_side_init(&cs, ray, cone);
    if (!cone_side_solve(&cs))
        return (false);
    if (cs.t0 > EPSILON)
    {
        m = cs.wv + cs.t0 * cs.dv;
        if (m >= 0.0 && m <= cone->height)
            return (*t_hit = cs.t0, true);
    }
    if (cs.t1 > EPSILON)
    {
        m = cs.wv + cs.t1 * cs.dv;
        if (m >= 0.0 && m <= cone->height)
            return (*t_hit = cs.t1, true);
    }
    return (false);
}

static bool	cone_base_hit(t_ray ray, t_cone *cone, double *t_hit)
{
    t_disk	disk;

    if (!cone || !t_hit)
        return (false);
    disk.center = vec3_add(cone->apex, vec3_scale(cone->axis, cone->height));
    disk.normal = cone->axis;
    disk.radius = cone->radius;
    return (intersect_disk(ray, disk, t_hit));
}

bool	intersect_cone(t_ray ray, t_cone *cone, double *t)
{
    double	t_side;
    double	t_base;
    bool	hit_side;
    bool	hit_base;

    if (!cone || !t)
        return (false);
    if (cone->radius <= 0.0 || cone->height <= 0.0)
        return (false);
    hit_side = cone_side_hit(ray, cone, &t_side);
    hit_base = cone_base_hit(ray, cone, &t_base);
    if (!hit_side && !hit_base)
        return (false);
    if (hit_side && (!hit_base || t_side < t_base))
        *t = t_side;
    else
        *t = t_base;
    return (true);
}