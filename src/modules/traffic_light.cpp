#include "modules/traffic_light.h"

using namespace godot;

void TrafficLight::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_go_texture","texture"),&TrafficLight::set_go_texture);
    ClassDB::bind_method(D_METHOD("get_go_texture"),&TrafficLight::get_go_texture);
    ClassDB::bind_method(D_METHOD("set_stop_texture","texture"),&TrafficLight::set_stop_texture);
    ClassDB::bind_method(D_METHOD("get_stop_texture"),&TrafficLight::get_stop_texture);
    ClassDB::bind_method(D_METHOD("set_caution_texture","texture"),&TrafficLight::set_caution_texture);
    ClassDB::bind_method(D_METHOD("get_caution_texture"),&TrafficLight::get_caution_texture);
    
    ClassDB::bind_method(D_METHOD("set_light_type","type"), &TrafficLight::set_light_type);
    ClassDB::bind_method(D_METHOD("get_light_type"), &TrafficLight::get_light_type);

    ClassDB::bind_method(D_METHOD("show_next_light"), &TrafficLight::show_next_light);
    
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "go_texture",PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),"set_go_texture","get_go_texture");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stop_texture",PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),"set_stop_texture","get_stop_texture");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caution_texture",PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),"set_caution_texture","get_caution_texture");

    ADD_PROPERTY(PropertyInfo(Variant::INT, "light_type",PROPERTY_HINT_ENUM, "Go,Stop,Caution"),"set_light_type","get_light_type");

    BIND_ENUM_CONSTANT(TRAFFIC_LIGHT_GO);
    BIND_ENUM_CONSTANT(TRAFFIC_LIGHT_STOP);
    BIND_ENUM_CONSTANT(TRAFFIC_LIGHT_CAUTION);

    ADD_SIGNAL(MethodInfo("light_changed", PropertyInfo(Variant::INT, "new_light")));
    GDVIRTUAL_BIND(_get_next_light,"current_light");
}

void TrafficLight::_notification(int p_what){
    switch (p_what){
        case NOTIFICATION_READY:
            set_light_type(light_type);
        break;
    }
        
}

void TrafficLight::set_go_texture(const Ref<Texture2D> &go_texture){
    this->go_texture = go_texture;
}

Ref<Texture2D> TrafficLight::get_go_texture() const{ 
    return go_texture;
}

void TrafficLight::set_stop_texture(const Ref<Texture2D> &stop_texture){
    this->stop_texture = stop_texture;
}

Ref<Texture2D> TrafficLight::get_stop_texture() const{
    return stop_texture;
}

void TrafficLight::set_caution_texture(const Ref<Texture2D> &caution_texture){
    this->caution_texture = caution_texture;
}

Ref<Texture2D> TrafficLight::get_caution_texture() const{
    return caution_texture;
}


void TrafficLight::set_light_type(TrafficLightType light_type){
    this->light_type = light_type;
     switch(light_type){
        case TRAFFIC_LIGHT_GO:
            texture_rect ->set_texture(go_texture);
        break;
        case TRAFFIC_LIGHT_CAUTION:
            texture_rect -> set_texture(caution_texture);
        break;
        case TRAFFIC_LIGHT_STOP:
            texture_rect-> set_texture(stop_texture);              
    }
    emit_signal("light_changed",light_type);
}

TrafficLightType TrafficLight::get_light_type() const{
    return light_type;
}

void TrafficLight::show_next_light() {
    TrafficLightType next_type;
    if(GDVIRTUAL_CALL(_get_next_light, light_type, next_type)){ //CHECK IF Method is not overrided
        set_light_type(next_type);
    }
}


TrafficLight::TrafficLight() {
    this->light_type = TRAFFIC_LIGHT_GO;
    texture_rect = memnew(TextureRect);
    add_child(texture_rect);
    texture_rect->set_anchors_preset(PRESET_FULL_RECT);

}