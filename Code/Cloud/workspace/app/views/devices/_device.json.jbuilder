json.extract! device, :id, :name, :ip, :status, :alarm_by_button, :alarm_by_sensor, :alarm_status_time, :temp, :created_at, :updated_at
json.url device_url(device, format: :json)