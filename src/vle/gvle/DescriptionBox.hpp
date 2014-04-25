

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
   void addDes(vpz::CoupledModel* parent,const std::string& src,
      const std::string& dst,
      const std::string& text);
   void queueRedraw()
   {  queue_draw(); }
   

private:
   gvle::ComboBoxString        m_comboInput;
   gvle::ComboBoxString        m_comboOutput;

   Gtk::Entry*                 m_entry;
   vpz::BaseModel*             src1;
   vpz::BaseModel*             dst1;
   vpz::CoupledModel*          parent1;
   
};

}
} // namespace vle gvle

#endif
