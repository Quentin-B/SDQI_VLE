

#ifndef GUI_DescriptionBox_HPP
#define GUI_DescriptionBox_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <vle/gvle/ComboboxString.hpp>
#include <vle/gvle/SimpleViewDrawingArea.hpp>

namespace vle
{
namespace vpz {

class CoupledModel;
class BaseModel;

}
} // namespace vle graph

namespace vle
{
namespace gvle {

/**
 * @brief A Gtk::Window to allow user to connect Model Atomic or Coupled.
 */
class DescriptionBox : public Gtk::Dialog
{
public:
    DescriptionBox(vpz::CoupledModel* parent, vpz::BaseModel* src,
                  vpz::BaseModel* dst);

    /**
     * Assign to string name value of combobox input
     *
     * @param name: string to assign value
     */
    void getSelectedInputPort(std::string& name) const {
        name.assign(m_comboInput.get_active_string());
    }

    /**
     * Assign to string name value of combobox output
     *
     * @param name: string to assign value
     */
    void getSelectedOutputPort(std::string& name) const {
        name.assign(m_comboOutput.get_active_string());
    }
    bool run();
std::string retext();

private:
    /**
     * Assign to combo box all inputs ports of model src if src equal
     * parent or ouputs otherwise.
     *
     * @param parent vpz::CoupledModel parent of src or equal
     * @param src children of parent
     */
    void assingComboInputPort(vpz::CoupledModel* parent,
                              vpz::BaseModel* src);

    /**
     * Assign to combo box all outputs ports of model dst if src equal
     * parent or inputs otherwise.
     *
     * @param parent vpz::CoupledModel parent of src or equal
     * @param src children of parent
     */
    void assingComboOutputPort(vpz::CoupledModel* parent,
                               vpz::BaseModel* dst);

    void addDes(vpz::CoupledModel* parent,const std::string& src,
                                      const std::string& dst,
                                      const std::string& text);
         void queueRedraw()
          {  queue_draw(); }
    

private:
    Gtk::VBox                   m_vbox;
    Gtk::HBox                   m_hbox;
    Gtk::Label                  m_label;
    Gtk::Frame                  m_left;
    Gtk::VBox                   m_left2;
    Gtk::Label                  m_labelInput;
    gvle::ComboBoxString        m_comboInput;
    Gtk::Frame                  m_right;
    Gtk::VBox                   m_right2;
    Gtk::Label                  m_labelOutput;
    gvle::ComboBoxString        m_comboOutput;
    SimpleViewDrawingArea*      mSimpleViewDrawingArea;


    Gtk::Label                  m_labelDescription;
    Gtk::Label                  m_description;
    Gtk::Entry*                 m_entry;
    vpz::BaseModel*             m_model;
    Gtk::HBox                   mHBox;

    vpz::BaseModel*             src1;
    vpz::BaseModel*             dst1;
    vpz::CoupledModel*          parent1;
        
};

}
} // namespace vle gvle

#endif
