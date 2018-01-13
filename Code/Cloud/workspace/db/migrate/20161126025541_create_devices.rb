class CreateDevices < ActiveRecord::Migration[5.0]
  def change
    create_table :devices do |t|
      t.string :name
      t.string :ip
      t.string :status
      t.string :alarm_by_button
      t.string :alarm_by_sensor
      t.string :alarm_status_time
      t.decimal :temp

      t.timestamps
    end
  end
end
