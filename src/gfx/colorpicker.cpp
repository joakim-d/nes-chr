#include "colorpicker.h"

#include "palette.h"
#include "rect.h"
#include "renderer.h"
#include "textgenerator.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"

#include <array>

const int PALETTE_COLOR_SIZE = 32;
const int COLOR_SIZE = 16;
const int Y_MARGIN = 70;
const int X_MARGIN = 16;

class ColorPaletteRect {
public:
  ColorPaletteRect(){}

  Rect rect_{};
};

class ColorPicker::ColorPickerPrivate {
public:
  ColorPickerPrivate(Engine &engine, Palette &palette) :
    engine_(engine), palette_(palette), text_generator_(engine.renderer(), "resources/PressStart2P.ttf", 24){
    colors_[0] = Color(124,124,124);
    colors_[1] = Color(0,0,252);
    colors_[2] = Color(0,0,188);
    colors_[3] = Color(68,40,188);
    colors_[4] = Color(148,0,132);
    colors_[5] = Color(168,0,32);
    colors_[6] = Color(168,16,0);
    colors_[7] = Color(136,20,0);
    colors_[8] = Color(80,48,0);
    colors_[9] = Color(0,120,0);
    colors_[10] = Color(0,104,0);
    colors_[11] = Color(0,88,0);
    colors_[12] = Color(0,64,88);
    colors_[13] = Color(0,0,0);
    colors_[14] = Color(0,0,0);
    colors_[15] = Color(0,0,0);
    colors_[16] = Color(188,188,188);
    colors_[17] = Color(0,120,248);
    colors_[18] = Color(0,88,248);
    colors_[19] = Color(104,68,252);
    colors_[20] = Color(216,0,204);
    colors_[21] = Color(228,0,88);
    colors_[22] = Color(248,56,0);
    colors_[23] = Color(228,92,16);
    colors_[24] = Color(172,124,0);
    colors_[25] = Color(0,184,0);
    colors_[26] = Color(0,168,0);
    colors_[27] = Color(0,168,68);
    colors_[28] = Color(0,136,136);
    colors_[29] = Color(0,0,0);
    colors_[30] = Color(0,0,0);
    colors_[31] = Color(0,0,0);
    colors_[32] = Color(248,248,248);
    colors_[33] = Color(60,188,252);
    colors_[34] = Color(104,136,252);
    colors_[35] = Color(152,120,248);
    colors_[36] = Color(248,120,248);
    colors_[37] = Color(248,88,152);
    colors_[38] = Color(248,120,88);
    colors_[39] = Color(252,160,68);
    colors_[40] = Color(248,184,0);
    colors_[41] = Color(184,248,24);
    colors_[42] = Color(88,216,84);
    colors_[43] = Color(88,248,152);
    colors_[44] = Color(0,232,216);
    colors_[45] = Color(120,120,120);
    colors_[46] = Color(0,0,0);
    colors_[47] = Color(0,0,0);
    colors_[48] = Color(252,252,252);
    colors_[49] = Color(164,228,252);
    colors_[50] = Color(184,184,248);
    colors_[51] = Color(216,184,248);
    colors_[52] = Color(248,184,248);
    colors_[53] = Color(248,164,192);
    colors_[54] = Color(240,208,176);
    colors_[55] = Color(252,224,168);
    colors_[56] = Color(248,216,120);
    colors_[57] = Color(216,248,120);
    colors_[58] = Color(184,248,184);
    colors_[59] = Color(184,248,216);
    colors_[60] = Color(0,252,252);
    colors_[61] = Color(248,216,248);
    colors_[62] = Color(0,0,0);
    colors_[63] = Color(0,0,0);

    number_textures_.push_back(text_generator_.textureFromText("0", Color(0,0,0)));
    number_textures_.push_back(text_generator_.textureFromText("1", Color(0,0,0)));
    number_textures_.push_back(text_generator_.textureFromText("2", Color(0,0,0)));
    number_textures_.push_back(text_generator_.textureFromText("3", Color(0,0,0)));
  }

  void handleEvents(){
    if(engine_.eventsListener().keyboardEvent(SDLK_0).pressed){
      selected_palette_index_ = 0;
    }
    else if(engine_.eventsListener().keyboardEvent(SDLK_1).pressed){
      selected_palette_index_ = 1;
    }
    if(engine_.eventsListener().keyboardEvent(SDLK_2).pressed){
      selected_palette_index_ = 2;
    }
    if(engine_.eventsListener().keyboardEvent(SDLK_3).pressed){
      selected_palette_index_ = 3;
    }
    auto mouse_event(engine_.eventsListener().mouseEvent());
    if(mouse_event.left_click){
      auto index = 0;
      for(auto &palette_rect: palette_rects_){
        if(palette_rect.rect_.contains(mouse_event.pos)){
          selected_palette_index_ = index;
          break;
        }
        index++;
      }

      index = 0;
      for(auto &colors_rect: colors_rects_){
        if(colors_rect.rect_.contains(mouse_event.pos)){
          palette_[selected_palette_index_] = colors_[index];
          break;
        }
        index++;
      }
    }

    //if(Rect(0, 0, ))
  }

  void render(){
    engine_.renderer().setDrawColor(Color(0,255,0));
    auto rect(palette_rects_[selected_palette_index_].rect_);
    rect.adjust(2);
    engine_.renderer().drawFillRect(rect);

    for(auto i = 0; i < 4; i++){
      engine_.renderer().setDrawColor(palette_[i]);
      engine_.renderer().drawFillRect(palette_rects_[i].rect_);
      engine_.renderer().renderTexture(number_textures_[i]);
    }

    for(std::size_t i = 0, end = colors_rects_.size(); i < end; i++){
      engine_.renderer().setDrawColor(colors_[i]);
      engine_.renderer().drawFillRect(colors_rects_[i].rect_);
    }
  }

  void setGlobalPos(const Pos &pos){
    pos_ = pos;
    for(auto i = 0; i < palette_rects_.size(); i++){
      number_textures_[i].setDstRect(Rect(pos_.x + i * (PALETTE_COLOR_SIZE + X_MARGIN), pos_.y, PALETTE_COLOR_SIZE, PALETTE_COLOR_SIZE));
      palette_rects_[i].rect_ = Rect(pos_.x + i * (PALETTE_COLOR_SIZE + X_MARGIN), pos_.y + PALETTE_COLOR_SIZE, PALETTE_COLOR_SIZE, PALETTE_COLOR_SIZE);
    }
    for(auto y = 0; y < 4; y++){
      for(auto x = 0; x < 16; x++){
        colors_rects_[y * 16 + x].rect_ = Rect(x * COLOR_SIZE + pos_.x, y * COLOR_SIZE + pos_.y + Y_MARGIN, COLOR_SIZE, COLOR_SIZE);
      }
    }
  }

  Engine &engine_;
  Palette &palette_;
  std::array<Color, 64> colors_;
  std::array<ColorPaletteRect, 4> palette_rects_;
  std::vector<Texture> number_textures_;
  std::array<ColorPaletteRect, 64> colors_rects_;
  Pos pos_;
  uint32_t selected_palette_index_{};
  TextGenerator text_generator_;
};

ColorPicker::ColorPicker(Engine &engine, Palette &palette) : d_(new ColorPickerPrivate(engine, palette)){}

ColorPicker::~ColorPicker() = default;

void ColorPicker::handleEvents(){
  d_->handleEvents();
}

void ColorPicker::render() {
  d_->render();
}

void ColorPicker::setGlobalPos(const Pos &pos){
  d_->setGlobalPos(pos);
}

void ColorPicker::initPalette() {
  d_->palette_[0] = d_->colors_[15];
  d_->palette_[1] = d_->colors_[5];
  d_->palette_[2] = d_->colors_[39];
  d_->palette_[3] = d_->colors_[8];
}

uint32_t ColorPicker::selectedPaletteColorIndex() const {
  return d_->selected_palette_index_;
}
