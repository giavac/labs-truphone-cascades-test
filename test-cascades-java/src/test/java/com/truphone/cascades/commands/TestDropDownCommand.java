package com.truphone.cascades.commands;

import java.io.PrintStream;

import org.junit.Assert;
import org.junit.Test;

import com.truphone.cascades.TimeoutException;
import com.truphone.cascades.replys.IReply;
import com.truphone.cascades.testutils.FakeDevice;
import com.truphone.cascades.testutils.FakeDevice.FakeDeviceListener;

/**
 * Test class.
 * @author STruscott
 *
 */
public final class TestDropDownCommand {
	/**
	 * Test the drop down command.
	 * @throws TimeoutException Thrown if the command times out
	 */
	@Test
	public void testDropDownCommand() throws TimeoutException {
		final FakeDeviceListener response = new FakeDeviceListener() {
			@Override
			public void messageReceived(String message, PrintStream replyStream) {
				if ("dropdown myList 10".equals(message) || "dropdown myList List option 4".equals(message)) {
					replyStream.println(FakeDevice.OK_MESSAGE);
				} else {
					Assert.fail(message);
				}
			}
		};
		FakeDevice.DEVICE.getProcess().addListener(response);
		final IReply reply1 = FakeDevice.CONN.transmit(new DropDownCommand("myList", 10), FakeDevice.DEFAULT_TIMEOUT);
		Assert.assertTrue(reply1.isSuccess());
		final IReply reply2 = FakeDevice.CONN.transmit(new DropDownCommand("myList", "List option 4"), FakeDevice.DEFAULT_TIMEOUT);
		FakeDevice.DEVICE.getProcess().removeListener(response);
		Assert.assertTrue(reply2.isSuccess());
	}
}
