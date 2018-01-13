require 'test_helper'

class DevicesControllerTest < ActionDispatch::IntegrationTest
  setup do
    @device = devices(:one)
  end

  test "should get index" do
    get devices_url
    assert_response :success
  end

  test "should get new" do
    get new_device_url
    assert_response :success
  end

  test "should create device" do
    assert_difference('Device.count') do
      post devices_url, params: { device: { alarm_by_button: @device.alarm_by_button, alarm_by_sensor: @device.alarm_by_sensor, alarm_status_time: @device.alarm_status_time, ip: @device.ip, name: @device.name, status: @device.status, temp: @device.temp } }
    end

    assert_redirected_to device_url(Device.last)
  end

  test "should show device" do
    get device_url(@device)
    assert_response :success
  end

  test "should get edit" do
    get edit_device_url(@device)
    assert_response :success
  end

  test "should update device" do
    patch device_url(@device), params: { device: { alarm_by_button: @device.alarm_by_button, alarm_by_sensor: @device.alarm_by_sensor, alarm_status_time: @device.alarm_status_time, ip: @device.ip, name: @device.name, status: @device.status, temp: @device.temp } }
    assert_redirected_to device_url(@device)
  end

  test "should destroy device" do
    assert_difference('Device.count', -1) do
      delete device_url(@device)
    end

    assert_redirected_to devices_url
  end
end
