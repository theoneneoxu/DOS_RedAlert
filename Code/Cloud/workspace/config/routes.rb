Rails.application.routes.draw do
  resources :devices
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  root 'devices#index'
  post 'device/device_online', to: 'devices#device_online'
  post 'device/device_offline', to:'devices#device_offline'
  post 'device/sensor_alarm', to: 'devices#sensor_alarm'
  post 'device/button_alarm', to:'devices#button_alarm'
  post 'device/update_temp', to:'devices#temp'
  get 'device/dismiss',to:'devices#dismiss'
end
