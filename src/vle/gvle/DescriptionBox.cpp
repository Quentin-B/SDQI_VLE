#include <vle/gvle/DescriptionBox.hpp>
#include <vle/vpz/CoupledModel.hpp>
#include <vle/utils/i18n.hpp>
#include <gtkmm/stock.h>
#include <cassert>
 #include <vle/gvle/SimpleViewDrawingArea.hpp>


using std::list;
using std::string;
using namespace vle;

namespace vle { namespace gvle {

DescriptionBox::DescriptionBox(vpz::CoupledModel* parent,
                             vpz::BaseModel* src,
                             vpz::BaseModel* dst) :
        Gtk::Dialog(_("Connection Description"), true, true),
        m_vbox(false),
        m_hbox(true),
        m_left(_("Source model")),
        m_left2(false),
        m_right(_("Destination model")),
        m_right2(false),
        src1(src),
        dst1(dst),
        parent1(parent)

{
    assert(parent and src and dst);
  
    assingComboInputPort(parent, src);
    assingComboOutputPort(parent, dst);

   set_position(Gtk::WIN_POS_MOUSE);
    Gtk::Button * okbutton;
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    okbutton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  
    m_entry = Gtk::manage(new Gtk::Entry());
      std::string label;
    label=parent->vpz::CoupledModel::getConnectionDescription(src->getName(),dst->getName());
    if (label!="0")
    {
        m_entry->set_text(label);
    }
  
    Gtk::Frame * frameNorth = Gtk::manage(new Gtk::Frame(_("Description:                                                         ")));
    frameNorth->set_border_width(5);
    frameNorth->set_shadow_type(Gtk::SHADOW_NONE);
    frameNorth->add(*m_entry);

    Gtk::VBox *vbox1 = Gtk::manage(new class Gtk::VBox(false, 0));
    vbox1->pack_start(*frameNorth, Gtk::PACK_SHRINK, 0);
  
    get_vbox()->add(*vbox1);
    get_vbox()->set_homogeneous(false);
    get_vbox()->set_spacing(0);

    okbutton->set_flags(Gtk::CAN_DEFAULT);
    okbutton->grab_default();
    m_entry->set_activates_default();

    show_all();

  
    queueRedraw();


}

bool DescriptionBox::run()
{
    for (;;) {
        int response = Gtk::Dialog::run();

        if (response == Gtk::RESPONSE_OK) {
            m_entry->get_text();
            addDes(parent1,src1->getName(),dst1->getName(),m_entry->get_text());
            hide();
            return true;
        }
         else {
            hide();
            return false;
        }
    }
}

std::string DescriptionBox::retext()
{
    return m_entry->get_text();
}
void DescriptionBox::addDes(vpz::CoupledModel* parent,const std::string& src,
                                      const std::string& dst,
                                      const std::string& text)
{
    parent ->vpz::CoupledModel::addConnectionDescription(src,dst,text);
}

void DescriptionBox::assingComboOutputPort(vpz::CoupledModel* parent,
        vpz::BaseModel* dst)
{
    if (dst == parent) {
        const vpz::ConnectionList& input = dst->getOutputPortList();
        vpz::ConnectionList::const_iterator it = input.begin();
        while (it != input.end()) {
            m_comboOutput.append_string((*it).first);
            ++it;
        }
    } else {
        const vpz::ConnectionList& input = dst->getInputPortList();
        vpz::ConnectionList::const_iterator it = input.begin();
        while (it != input.end()) {
            m_comboOutput.append_string((*it).first);
            ++it;
        }
    }
}

void DescriptionBox::assingComboInputPort(vpz::CoupledModel* parent,
        vpz::BaseModel* src)
{
    if (src == parent) {
        const vpz::ConnectionList& output = src->getInputPortList();
        vpz::ConnectionList::const_iterator it = output.begin();
        while (it != output.end()) {
            m_comboInput.append_string((*it).first);
            ++it;
        }
    } else {
        const vpz::ConnectionList& output = src->getOutputPortList();
        vpz::ConnectionList::const_iterator it = output.begin();
        while (it != output.end()) {
            m_comboInput.append_string((*it).first);
            ++it;
        }
    }
}

}
} // namespace vle gvle
